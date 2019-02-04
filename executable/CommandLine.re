open Cmdliner;

let portTerm = {
  let doc = "Set the server port to $(docv).";

  Arg.(value & opt(int, 8000) & info(["p", "port"], ~docv="PORT", ~doc));
};

let run = port => {
  let server = Rudolph.Server.make(port);

  let () = ignore(Lwt_main.run(server));
  ();
};

let terms = Term.(const(run) $ portTerm);

let info = Term.info("rudolph");

let () = Term.exit @@ Term.eval((terms, info));
