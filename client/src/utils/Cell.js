import React from "react";
import {Guesstimator} from '../lib/guesstimator/index';

export class Cell extends React.Component {
    constructor(props) {
        super(props);
        this.state = {value: ''};
        this.handleChange = this.handleChange.bind(this);
    }
    handleChange(event) {
        this.setState({value: event.target.value});
      }

    render() {
        return (<div><input type="text" value={this.state.value} onChange={this.handleChange}/></div>)
    }
}