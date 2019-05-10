open Css;

let component = ReasonReact.statelessComponent("divWithStyles");
let make = (~styles=[], ~flex=?, ~flexDirection=?, ~float=?, children) => {
  ...component,
  render: _ => {
    let flexStyle =
      flex |> E.O.fmap(e => Css.style([Css.flex(e)])) |> E.O.default("");
    let floatStyle =
      float |> E.O.fmap(e => Css.style([Css.float(e)])) |> E.O.default("");
    let directionStyle =
      flexDirection
      |> E.O.fmap(e => Css.style([display(`flex), Css.flexDirection(e)]))
      |> E.O.default("");
    let allStyles = [flexStyle, directionStyle, floatStyle, ...styles];
    <div className={E.L.join(" ", allStyles)}> ...children </div>;
  },
};