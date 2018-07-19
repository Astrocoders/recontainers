let component = ReasonReact.statelessComponent("ReComponent");

let make =
    (~willUnmount=ignore, ~willUpdate=ignore, ~didMount=ignore, children) => {
  ...component,
  didMount,
  willUpdate,
  willUnmount,
  render: self => children(self),
};
