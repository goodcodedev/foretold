let component = ReasonReact.statelessComponent("Link");

type linkType =
  | Action(ReactEvent.Mouse.t => unit)
  | Internal(Context.Routing.Url.t)
  | External(string);

module LinkType = {
  type t = linkType;

  let toString = t: string =>
    switch (t) {
    | Internal(r) => r |> Context.Routing.Url.toString
    | External(s) => s
    | Action(_) => "#"
    };

  let handleStringUrlClick = (event: ReactEvent.Mouse.t, href) =>
    /* This needed to make sure the page isn't reloaded */
    if (!ReactEvent.Mouse.defaultPrevented(event)) {
      ReactEvent.Mouse.preventDefault(event);
      ReasonReact.Router.push(href);
    };

  let onClick = (t: t, event) =>
    switch (t) {
    | Action(action) => action(event)
    | _ => handleStringUrlClick(event, t |> toString)
    };
};

let make = (~linkType: linkType, ~className: option(string)=?, children) => {
  ...component,
  render: _self =>
    <a
      href={LinkType.toString(linkType)}
      ?className
      onClick={LinkType.onClick(linkType)}>
      ...children
    </a>,
};