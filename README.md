# game-server-skeleton

A small HTTP server for finding out what a game asks its online service for. It logs every call in full and answers 404 to anything not handled yet, so you can add the endpoints the game needs one at a time. 



 The server reads `config.json` from the directory it is started in

## Configuration

```json
{
    "listen": { "address": "0.0.0.0", "port": 8080 },
    "base_path": "/game/v1",
    "log": { "file": "server.log", "max_size_mb": 10 }
}
```

| Key                             | Meaning                                                                                         |
| ------------------------------- | ----------------------------------------------------------------------------------------------- |
| `listen.address`, `listen.port` | where the server listens                                                                        |
| `base_path`                     | prefix in front of every endpoint,requests outside it are logged and answered 404. Empty = none |
| `log.file`                      | log file, relative to the config file, empty = console only                                     |
| `log.max_size_mb`               | 1 to 4096: when the file reaches this size it is rewritten from the start                       |

## What gets logged

Each call: the method, path and query, the client address, every header, and the body (as text when it is printable, otherwise as hex, the first 512 bytes). Calls with no handler are marked:

```
2026-10-17 23:01:46 [info] POST /game/v1/redrw.php?v=3 from 127.0.0.1
2026-10-17 23:01:46 [info]   x-np-authcode: ABC123,256
2026-10-17 23:01:46 [info]   body 16 bytes: {"serial":[1,2]}
2026-10-17 23:01:46 [warning] unhandled: POST redrw.php
```

## Adding endpoints

Every request reaches `handleRequest` in `src/handler.cpp` with `endpoint` = the path below
`base_path`. Add a branch per endpoint above the 404 at the end.

```cpp
if (endpoint == QLatin1String("regev.php")) {
    HttpResponse response;
    response.contentType = "application/json";
    response.body = "{}";
    respond(response);
    return;
}
```
