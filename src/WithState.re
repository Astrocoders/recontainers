module type Config = {type state;};

module Make = (Config: Config) => {
  type action =
    | Set(Config.state);

  type interface = {
    state: Config.state,
    send: action => unit,
  };

  [@react.component]
  let make =
      (
        ~initialState,
        ~didMount=ignore,
        ~willUpdate=ignore,
        ~willUnmount=ignore,
        ~children,
        (),
      ) => {
    let (state, send) =
      React.useReducer(
        _ =>
          fun
          | Set(newState) => newState,
        initialState,
      );

    Component.use(~willUnmount, ~willUpdate, ~didMount, ());

    children({state, send});
  };
};
