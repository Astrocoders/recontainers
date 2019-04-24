let component = ReasonReact.statelessComponent("ReComponent");

[@react.component]
let make =
    (~willUnmount=ignore, ~willUpdate=ignore, ~didMount=ignore, ~children) =>
  ReactCompat.useRecordApi({
    ...component,
    didMount,
    willUpdate,
    willUnmount,
    render: self => children(self),
  });
