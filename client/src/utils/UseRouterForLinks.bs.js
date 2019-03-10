// Generated by BUCKLESCRIPT VERSION 4.0.6, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var Curry = require("bs-platform/lib/js/curry.js");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");

var component = ReasonReact.statelessComponent("UseRouterForLinks");

var outer = Css.style(/* :: */[
      Css.height(/* `percent */[
            -119887163,
            100.0
          ]),
      /* [] */0
    ]);

var Styles = /* module */[/* outer */outer];

function make($staropt$star, children) {
  var onClickData = $staropt$star !== undefined ? $staropt$star : (function () {
        return /* () */0;
      });
  var click = function ($$event) {
    if ($$event.target.localName === "a") {
      var data = $$event.target.getAttribute("data");
      if (data == null) {
        var url = $$event.target.getAttribute("href");
        $$event.preventDefault();
        return ReasonReact.Router[/* push */0](url);
      } else {
        $$event.preventDefault();
        return Curry._1(onClickData, data);
      }
    } else {
      return 0;
    }
  };
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              return ReactDOMRe.createElementVariadic("div", {
                          className: outer,
                          onClick: click
                        }, children);
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.Styles = Styles;
exports.make = make;
/* component Not a pure module */