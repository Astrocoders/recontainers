module type Config = {type t;};

module Make = (Config: Config) => {
  type state =
    | Empty
    | Loading
    | Error(string)
    | Success(Config.t);
  type action =
    | Dispatch(Js.Promise.t(Config.t))
    | SetState(state);

  let component = ReasonReact.reducerComponent("ReLoader");
  type children =
    (
      ~state: state,
      ~load: Js.Promise.t(Config.t) => unit,
      ~reset: unit => unit
    ) =>
    ReasonReact.reactElement;
  let make = (children: children) => {
    ...component,
    initialState: () => Empty,
    reducer: (action, _state) =>
      switch (action) {
      | Dispatch(promise) =>
        UpdateWithSideEffects(
          Loading,
          (
            self =>
              Js.Promise.(
                promise
                |> then_(result =>
                     self.send(SetState(Success(result))) |> resolve
                   )
                |> catch(_err => {
                     self.send(SetState(Error("Something went wrong")));
                     resolve();
                   })
                |> ignore
              )
          ),
        )
      | SetState(state) => Update(state)
      },
    render: self => {
      let load = promise => self.send(Dispatch(promise));
      let reset = () => self.send(SetState(Empty));

      children(~state=self.state, ~load, ~reset);
    },
  };
};
