const Sequelize = require('sequelize');
const _ = require('lodash');
const fetch = require("node-fetch");
const moment = require('moment');

const { clientUrl } = require('../lib/urls');

const { MEASURABLE_STATE } = require('./measurable-state');

module.exports = (sequelize, DataTypes) => {
  const Model = sequelize.define('Measurable', {
    id: {
      type: DataTypes.UUID(),
      primaryKey: true,
      defaultValue: DataTypes.UUIDV4,
      allowNull: false,
    },

    // Meta
    name: {
      type: DataTypes.STRING,
      allowNull: false,
    },
    labelSubject: {
      type: DataTypes.STRING,
      allowNull: true,
    },
    labelOnDate: {
      type: DataTypes.DATE,
      allowNull: true,
    },
    labelProperty: {
      type: DataTypes.STRING,
      allowNull: true,
    },
    labelCustom: {
      type: DataTypes.TEXT,
      allowNull: true,
    },
    valueType: {
      type: DataTypes.ENUM(["FLOAT", "DATE", "PERCENTAGE"]),
      allowNull: false,
    },

    // State
    state: {
      type: DataTypes.STRING,
      defaultValue: MEASURABLE_STATE.OPEN,
      allowNull: false,
    },
    stateUpdatedAt: {
      allowNull: true,
      type: DataTypes.DATE
    },

    // Status
    isArchived: {
      type: DataTypes.BOOLEAN,
      allowNull: false,
      defaultValue: false,
    },

    // Resolution
    resolutionEndpoint: {
      type: DataTypes.TEXT,
      allowNull: true,
    },
    expectedResolutionDate: {
      allowNull: true,
      type: DataTypes.DATE
    },

    // Link
    channelId: {
      type: DataTypes.UUID(),
      allowNull: false,
    },

    // Counts
    measurementCount: {
      allowNull: true,
      type: Sequelize.VIRTUAL(DataTypes.INTEGER),
      get: async function () {
        const items = await this.getMeasurements();
        return items.length
      }
    },
    measurerCount: {
      allowNull: true,
      type: Sequelize.VIRTUAL(DataTypes.INTEGER),
      get: async function () {
        const items = await this.getMeasurements();
        return _.uniq(items.map(i => i.agentId)).length
      }
    },

    // Satellite
    resolutionEndpointResponse: {
      allowNull: true,
      type: Sequelize.VIRTUAL(DataTypes.FLOAT),
      get: async function resolutionEndpointResponseGetter() {
        const endpoint = await this.dataValues.resolutionEndpoint;
        if (!endpoint) return false;
        try {
          const response = await fetch(endpoint);
          const json = await response.json();
          const match = JSON.stringify(json).match(/[-+]?[0-9]*\.?[0-9]+/);
          const asFloat = parseFloat(match[0]);
          console.log(`got response from endpoint. Url: ${endpoint}, Response: ${JSON.stringify(json)}, Float: ${asFloat}`);
          return asFloat;
        } catch (e) {
          console.error(`Error getting response from endpoint. Url: ${endpoint}, error: ${e}`);
          return null;
        }
      }
    },
  });

  Model.needsResolutionResponse = async function needsResolutionResponse() {
    return await Model.findAll({
      where: {
        state: MEASURABLE_STATE.JUDGEMENT_PENDING,
        expectedResolutionDate: {
          [Sequelize.Op.lt]: Sequelize.fn('now'),
        }
      }
    })
  };

  Model.needsToBePending = async function needsToBePending() {
    return await Model.findAll({
      where: {
        state: MEASURABLE_STATE.OPEN,
        [Sequelize.Op.or]: [
          {
            expectedResolutionDate: {
              [Sequelize.Op.lt]: Sequelize.fn('now'),
            }
          },
          { expectedResolutionDate: null },
        ],
      }
    })
  };

  Model.prototype.updateState = async function updateState(state) {
    await this.update({ state, stateUpdatedAt: Sequelize.fn('now') });
  };

  Model.prototype.archive = async function archive() {
    await this.update({ isArchived: true });
  };

  Model.prototype.unarchive = async function unarchive() {
    await this.update({ isArchived: false });
  };

  Model.prototype.judged = async function judged() {
    await this.updateState(MEASURABLE_STATE.JUDGED);
  };

  Model.prototype.judgementPending = async function judgementPending() {
    await this.updateState(MEASURABLE_STATE.JUDGEMENT_PENDING);
  };

  /**
   * @param {Models.Agent.id} agentId
   * @return {Promise<void>}
   */
  Model.prototype.processResolution = async function processResolution(agentId) {
    const asFloat = await this.resolutionEndpointResponse;
    if (asFloat) {
      await sequelize.models.Measurement.create({
        agentId,
        competitorType: "OBJECTIVE",
        measurableId: this.dataValues.id,
        value: { "dataType": "floatPoint", "data": asFloat }
      });
    }
    await this.judged();
  };

  /**
   * @todo: move me
   * @public
   * @param {Models.Creator} creator
   * @return {Promise<*>}
   */
  Model.prototype.creationNotification = async function creationNotification(creator) {
    let agent = await creator.getAgent();
    let notification = {
      "attachments": [{
        "pretext": "New Measurable Created",
        "title": this.name,
        "title_link": `${clientUrl}/measurables/${this.id}`,
        "author_name": creator.name,
        "author_link": `${clientUrl}/agents/${agent.id}`,
        "text": this.labelCustom,
        "fields": [
          {
            "title": "Resolution Date",
            "value": moment(this.expectedResolutionDate).format("MMM DD, YYYY"),
            "short": true
          }
        ],
        "color": "#4a8ed8"
      }]
    };
    return notification;
  };

  /**
   * @param {object} ops
   * @return {string[]}
   */
  Model.prototype.changedFields = function changedFields(ops) {
    return Object.keys(ops).filter(r => r !== "expectedResolutionDate").filter(r => this[r] !== ops[r]);
  };

  /**
   * @todo: move me
   * @public
   * @param {Models.Creator} creator
   * @param {object} newData
   * @return {Promise<*>}
   */
  Model.prototype.updateNotifications = async function updateNotifications(creator, newData) {
    let changed = this.changedFields(newData);
    let agent = await creator.getAgent();
    let notification = {
      "attachments": [{
        "pretext": "Measurable Updated",
        "title": this.name,
        "title_link": `${clientUrl}/measurables/${this.id}`,
        "author_name": creator.name,
        "author_link": `${clientUrl}/agents/${agent.id}`,
        "fields": changed.map(c => ({
          "title": c,
          "short": false,
          "value": `*From*: ${this[c]} \n*To*:  ${newData[c]}`
        })),
        "color": "#ffe75e"
      }]
    };
    return notification;
  };

  Model.associate = function associate(models) {
    Model.Measurements = Model.hasMany(models.Measurement, {
      foreignKey: 'measurableId',
      as: 'Measurements'
    });

    Model.Series = Model.belongsTo(models.Series, {
      foreignKey: 'seriesId',
      as: "series"
    });

    Model.Creator = Model.belongsTo(models.Agent, {
      foreignKey: 'creatorId',
      as: 'creator'
    });

    // Usage:
    // const me = await models.Measurable.find();
    // const ch = await me.getChannel();
    Model.Channel = Model.belongsTo(models.Channel, {
      foreignKey: 'channelId',
    });
  };

  return Model;
};
