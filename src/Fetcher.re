module type Config = {type t;};

module Make = (Config: Config) => {
  type state =
    | Empty
    | Fetching
    | Error(string)
    | Success(Config.t);
  type action =
    | Dispatch(Js.Promise.t(Config.t))
    | SetState(state);

  type api = {
    state,
    load: Js.Promise.t(Config.t) => unit,
    reset: unit => unit,
  };

  let component = ReasonReact.reducerComponent("ReFetcher");
  [@react.component]
  let make = (~children) =>
    ReactCompat.useRecordApi({
      ...component,
      initialState: () => Empty,
      reducer: (action, _state) =>
        switch (action) {
        | Dispatch(promise) =>
          UpdateWithSideEffects(
            Fetching,
            self =>
              Js.Promise.(
                promise
                |> then_(result =>
                     self.send(SetState(Success(result))) |> resolve
                   )
                |> catch(_err => {
                     /* TODO: give error back to user*/
                     self.send(SetState(Error("Something went wrong")));
                     resolve();
                   })
                |> ignore
              ),
          )
        | SetState(state) => Update(state)
        },
      render: self => {
        let load = promise => self.send(Dispatch(promise));
        let reset = () => self.send(SetState(Empty));

        children({state: self.state, load, reset});
      },
    });
};
