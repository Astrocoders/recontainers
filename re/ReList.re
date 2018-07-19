module type Config = {type t;};

module Make = (Config: Config) => {
  type state = list(Config.t);
  type action =
    | Reset
    | Push(Config.t)
    | Pull(Config.t => bool)
    | Map(Config.t => Config.t);

  let component = ReasonReact.reducerComponent("ReList");

  type api = {
    list: state,
    pull: (Config.t => bool) => unit,
    map: (Config.t => Config.t) => unit,
    push: (Config.t, unit) => unit,
  };

  let make = (~initial=[], children) => {
    ...component,
    initialState: () => initial,
    reducer: (action, state) =>
      switch (action) {
      | Reset => Update([])
      | Push(value) => Update([value, ...state])
      | Pull(predicate) => Update(List.filter(predicate, state))
      | Map(map) => Update(List.map(map, state))
      },
    render: self =>
      children({
        list: self.state,
        pull: predicate => self.send(Pull(predicate)),
        map: map => self.send(Map(map)),
        push: (value, ()) => self.send(Push(value)),
      }),
  };
};
