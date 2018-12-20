module type Config = {type state;};

module Make = (Config: Config) => {
  type action =
    | Set(Config.state);

  let component = ReasonReact.reducerComponent("WithState");

  let make =
      (
        ~initialState,
        ~didMount=ignore,
        ~willUpdate=ignore,
        ~willUnmount=ignore,
        children,
      ) => {
    ...component,
    initialState: () => initialState,
    didMount,
    willUpdate,
    willUnmount,
    reducer: (action, _state) =>
      switch (action) {
      | Set(newState) => Update(newState)
      },
    render: self => children(self),
  };
};
