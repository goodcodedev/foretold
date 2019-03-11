module BorderedBox = {
  let component = ReasonReact.statelessComponent("BorderedBox");
  module Styles = {
    open Css;
    let item =
      style([
        maxWidth(px(1500)),
        display(`flex),
        flexDirection(`row),
        padding(px(12)),
        borderRadius(px(2)),
        border(px(1), `solid, `hex("eee")),
        marginBottom(px(20)),
      ]);
  };

  let make = children => {
    ...component,
    render: _ => <div className=Styles.item> ...children </div>,
  };
};

module Grid = {
  open Css;

  module Div = {
    let component = ReasonReact.statelessComponent("divWithStyles");
    let make = (~styles=[], ~flex=?, ~flexDirection=?, children) => {
      ...component,
      render: _ => {
        let flexStyle =
          flex
          |> E.O.fmap(e => Css.style([Css.flex(e)]))
          |> E.O.default("bbb");
        let directionStyle =
          flexDirection
          |> E.O.fmap(e =>
               Css.style([display(`flex), Css.flexDirection(e)])
             )
          |> E.O.default("yoyyoyo");
        let allStyles = [flexStyle, directionStyle, ...styles];
        <div className={E.L.join(" ", allStyles)}> ...children </div>;
      },
    };
  };
};