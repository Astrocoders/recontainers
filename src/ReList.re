type state('a) = list('a);
type action('a, 'b) =
  | Reset
  | Push('a)
  | Pull('a => bool)
  | Map('a => 'b);

type api('a, 'b) = {
  list: state('a),
  pull: ('a => bool) => unit,
  map: ('a => 'b) => unit,
  push: ('a, unit) => unit,
};

let use = (~initial) => {
  let (state, send) =
    React.useReducer(
      state =>
        fun
        | Reset => []
        | Push(value) => [value, ...state]
        | Pull(predicate) => List.filter(item => !predicate(item), state)
        | Map(map) => List.map(map, state),
      initial,
    );
  {
    list: state,
    pull: predicate => send(Pull(predicate)),
    map: map => send(Map(map)),
    push: (value, _) => send(Push(value)),
  };
};

[@react.component]
let make = (~initial=[], children) => {
  let api = use(~initial);
  children(api);
};
