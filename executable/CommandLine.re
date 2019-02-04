open Cmdliner;

let portTerm = {
  let doc = "Repeat the message $(docv) times.";

  Arg.(value & opt(int, 8000) & info(["p", "port"], ~docv="PORT", ~doc));
};

let run = port => {
  let server = Rudolph.Server.make(port);

  let () = ignore(Lwt_main.run(server));
  ();
};

let terms = Term.(const(run) $ portTerm);

let info = Term.info("");

let () = Term.exit @@ Term.eval((terms, info));
