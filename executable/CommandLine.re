open Cmdliner;

let portTerm = {
  let doc = "Set the server port to $(docv).";

  Arg.(value & opt(int, 8000) & info(["p", "port"], ~docv="PORT", ~doc));
};

let bundlerTerm = {
  let doc = "Bundler command to run.";

  Arg.(
    value
    & opt(some(string), None)
    & info(["bundler"], ~docv="BUNDLER", ~doc)
  );
};

let bundlerOptionsTerm = {
  let doc = "wat wat?";

  Arg.(value & pos_all(string, []) & info([], ~docv="REST?", ~doc));
};

let run = (port, bundler, bundlerOptions) => {
  let cmd =
    switch (bundler) {
    | Some(bundler) =>
      let f = (result, next) =>
        switch (result) {
        | None => Some(next)
        | Some(result) => Some(result ++ " " ++ next)
        };
      let init = None;
      ListLabels.fold_left(~f, ~init, [bundler, ...bundlerOptions]);
    | None => None
    };

  let server = Rudolph.Server.make(port, cmd);

  ignore(Lwt_main.run(server));
};

let terms = Term.(const(run) $ portTerm $ bundlerTerm $ bundlerOptionsTerm);

let info = Term.info("rudolph");

let () = Term.exit @@ Term.eval((terms, info));
