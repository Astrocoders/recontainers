type state('a) =
  | Empty
  | Fetching
  | Error(string)
  | Success('a);

type action('a) =
  | Dispatch(Js.Promise.t('a))
  | SetState(state('a));

type api('a) = {
  state: state('a),
  load: Js.Promise.t('a) => unit,
  reset: unit => unit,
};

let use = (~promise=?, ()) => {
  let (state, setState) = React.useState(() => Empty);

  let load = promise => {
    Js.Promise.(
      promise
      |> then_(result => setState(_ => Success(result)) |> resolve)
      |> catch(_err => {
           /* TODO: give error back to user */
           setState(_ => Error("Something went wrong"));
           resolve();
         })
      |> ignore
    );
  };

  let reset = () => setState(_ => Empty);

  React.useEffect0(() => {
    switch (promise) {
    | Some(promise) => load(promise) |> ignore
    | None => ()
    };
    None;
  });

  {state, reset, load};
};
