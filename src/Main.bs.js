// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Http = require("http");
var Future = require("@qwick/future/src/Future.bs.js");
var Rollup = require("./bindings/Rollup.bs.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var ServeHandler = require("serve-handler");
var SimpleHtmlIndex = require("simple-html-index");

function build(param) {
  var inputOptions = Rollup.InputOptions[/* make */0]("index.js");
  var outputOptions = Rollup.OutputOptions[/* make */0]("iife", "output.js");
  return Future.mapOk(Future.mapOk(Future.flatMapOk(Rollup.rollup(inputOptions), (function (bundle) {
                        return Rollup.Bundle[/* generate */0](bundle, outputOptions);
                      })), (function (output) {
                    return Belt_Array.keep(output.output, (function (chunk) {
                                  return Rollup.Chunk[/* isEntry */1](chunk);
                                }));
                  })), (function (chunks) {
                return Caml_array.caml_array_get(chunks, 0).code;
              }));
}

var server = Http.createServer((function (request, response) {
        ServeHandler(request, response, undefined, {
              createReadStream: (function (path, config) {
                  return SimpleHtmlIndex({
                              title: "test",
                              entry: "bundle.js"
                            });
                })
            });
        return /* () */0;
      }));

server.listen(3000, (function (param) {
        console.log("Running at http://localhost:3000");
        return /* () */0;
      }));

exports.build = build;
exports.server = server;
/* server Not a pure module */
