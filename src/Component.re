let use = (~willUnmount=ignore, ~willUpdate=ignore, ~didMount=ignore, ()) => {
  React.useEffect0(() => {
    didMount();
    Some(willUnmount);
  });
  React.useEffect(() => {
    willUpdate();
    None;
  });
};

[@react.component]
let make =
    (~willUnmount=ignore, ~willUpdate=ignore, ~didMount=ignore, ~children, ()) => {
  use(~willUnmount, ~willUpdate, ~didMount, ());
  children();
};
