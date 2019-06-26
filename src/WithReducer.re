module type Config = {
  type state;
  type action;
};

module Make = (Config: Config) => {
  open Config;

  type interface = {
    state: Config.state,
    send: action => unit,
  };

  [@react.component]
  let make =
      (
        ~initialState: state,
        ~reducer,
        ~didMount: interface => unit=?,
        ~willUnmount: unit => unit=?,
        ~willUpdate: interface => unit=?,
        ~children,
        (),
      ) => {
    let (state, send) =
      React.useReducer(
        (state, action) => reducer(action, state),
        initialState,
      );
    let self = {state, send};
    React.useEffect0(() => {
      didMount(self);
      Some(willUnmount);
    });
    React.useEffect(() => {
      willUpdate(self);
      None;
    });
    children(self);
  };
};
