module type Config = {type state;};

module Make = (Config: Config) => {
  type action =
    | Set(Config.state);

  let component = ReasonReact.reducerComponent("WithState");

  let make = ( ~initialState, children ) => {
    ...component,
    initialState: () => initialState,
    reducer: (action, _state) =>
      switch (action) {
      | Set(newState) => Update(newState)
      },
    render: self => children(self),
  };
};

