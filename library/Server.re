open Lwt;
open Cohttp;
open Cohttp_lwt_unix;

let make = (port, bundler) => {
  let callback = (_conn, req, body) => {
    switch (req->Request.meth) {
    | `GET =>
      /* let uri = req |> Request.uri |> Uri.to_string; */
      /* let meth = req |> Request.meth |> Code.string_of_method; */
      /* let headers = req |> Request.headers |> Header.to_string; */
      switch (bundler) {
      | Some(bundler) =>
        let cmd = Lwt_process.(bundler->shell->pread_lines);
        Server.respond(
          ~status=`OK,
          ~body=Cohttp_lwt.Body.of_stream(cmd),
          (),
        );
      | None => Server.respond_string(~status=`OK, ~body="Hello World", ())
      }
    | _ =>
      Server.respond_error(
        ~status=`Method_not_allowed,
        ~body="Rudolph only accepts GET requests.",
        (),
      )
    };
  };

  Server.create(~mode=`TCP(`Port(port)), Server.make(~callback, ()));
};
