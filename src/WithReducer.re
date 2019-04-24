module type Config = {
  type state;
  type action;
};

module Make = (Config: Config) => {
  open Config;

  type self = ReasonReact.self(state, ReasonReact.noRetainedProps, action);
  type oldNewSelf =
    ReasonReact.oldNewSelf(state, ReasonReact.noRetainedProps, action);

  let component = ReasonReact.reducerComponent("WithState");

  let make:
    (
      ~initialState: state,
      ~reducer: (action, state) =>
                ReasonReact.update(state, ReasonReact.noRetainedProps, action),
      ~didMount: self => unit=?,
      ~willUnmount: self => unit=?,
      ~willUpdate: oldNewSelf => unit=?,
      'a
    ) =>
    ReasonReact.componentSpec(
      state,
      state,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      action,
    ) =
    (
      ~initialState,
      ~reducer,
      ~didMount=ignore,
      ~willUnmount=ignore,
      ~willUpdate=ignore,
      children,
    ) => {
      ...component,
      initialState: () => initialState,
      didMount,
      willUnmount,
      willUpdate,
      reducer,
      render: self => children(self),
    };
};
