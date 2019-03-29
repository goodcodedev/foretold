const data = require('../data');

/**
 * @param {*} root
 * @param {{channelId: string, agentId: string, role: string}} args
 * @returns {Promise<Model>}
 */
async function create(root, args) {
  return await data.channelsMembershipsData.createOne(
    args.channelId,
    args.agentId,
    args.role
  );
}

/**
 * @param root
 * @param {{channelId: string, agentId: string, role: string}} args
 * @returns {Promise<Model>}
 */
async function update(root, args) {
  return await data.channelsMembershipsData.updateOne(
    args.channelId,
    args.agentId,
    args.role
  );
}

/**
 * @param root
 * @param {{channelId: string, agentId: string}} args
 * @returns {Promise<Model>}
 */
async function remove(root, args) {
  return await data.channelsMembershipsData.deleteOne(
    args.channelId,
    args.agentId
  );
}

module.exports = {
  remove,
  create,
  update,
};