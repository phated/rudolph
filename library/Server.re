open Lwt;
open Cohttp;
open Cohttp_lwt_unix;

let make = port => {
  let callback = (_conn, req, body) => {
    switch (req->Request.meth) {
    | `GET =>
      let uri = req |> Request.uri |> Uri.to_string;
      let meth = req |> Request.meth |> Code.string_of_method;
      let headers = req |> Request.headers |> Header.to_string;
      body
      |> Cohttp_lwt.Body.to_string
      >|= (
        body =>
          Printf.sprintf(
            "Uri: %s\nMethod: %s\nHeaders\nHeaders: %s\nBody: %s",
            uri,
            meth,
            headers,
            body,
          )
      )
      >>= (body => Server.respond_string(~status=`OK, ~body, ()));
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
