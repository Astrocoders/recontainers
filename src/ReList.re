module type Config = {type t;};

module Make = (Config: Config) => {
  type state = list(Config.t);
  type action =
    | Reset
    | Push(Config.t)
    | Pull(Config.t => bool)
    | Map(Config.t => Config.t);

  type api = {
    list: state,
    pull: (Config.t => bool) => unit,
    map: (Config.t => Config.t) => unit,
    push: (Config.t, unit) => unit,
  };

  let component = ReasonReact.reducerComponent("ReList");

  [@react.component]
  let make = (~initial=[], children) =>
    ReactCompat.useRecordApi({
      ...component,
      initialState: () => initial,
      reducer: (action, state) =>
        switch (action) {
        | Reset => Update([])
        | Push(value) => Update([value, ...state])
        | Pull(predicate) =>
          Update(List.filter(item => !predicate(item), state))
        | Map(map) => Update(List.map(map, state))
        },
      render: self =>
        children({
          list: self.state,
          pull: predicate => self.send(Pull(predicate)),
          map: map => self.send(Map(map)),
          push: (value, _) => self.send(Push(value)),
        }),
    });
};
