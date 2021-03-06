let component = ReasonReact.statelessComponent("StatSummary");

module Styles = {
  open Css;
  let textOverlay = style([position(`absolute)]);
  let mainText = style([fontSize(`em(1.1)), color(FC__Colors.darkLink)]);
  let secondaryText =
    style([fontSize(`em(0.9)), color(FC__Colors.accentBlue)]);
};

let make = (~cdf: Stats.dist, _children) => {
  ...component,
  render: _ =>
    <>
      <div className=Styles.mainText>
        {
          cdf
          |> Stats.findX(0.5)
          |> FC__E.Float.with3DigitsPrecision
          |> ReasonReact.string
        }
      </div>
      <div className=Styles.secondaryText>
        {
          cdf
          |> Stats.findX(0.05)
          |> FC__E.Float.with3DigitsPrecision
          |> ReasonReact.string
        }
        {" to " |> ReasonReact.string}
        {
          cdf
          |> Stats.findX(0.95)
          |> FC__E.Float.with3DigitsPrecision
          |> ReasonReact.string
        }
      </div>
    </>,
};