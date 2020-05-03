# ric

"Weddings are basically funerals with cake."

by Rick, from "Rick and Morty"

ric is an implementation of:
- Sanguino, J., "A Quick Guide to Networking Software", 5th Edition, Feb 2020

It also aggregates all tasks into a single program called ric.

The name is a pun to the Course from which the guide is (RCI), as well as the
spirit of the project itself, which tries to expose more of the cool stuff, in
a bold and sarcastic manner of the one Rick.

## Correspondence

- hname.c        -- task 1: gethostname
- nslook.c       -- task 2: getaddrinfo
- udp\_client.c   -- task 3, 4, 5: udp\_client
- tcp\_client.c   -- task 6, 7, 8: tcp\_client
- udp\_server.c   -- task 9: udp\_server
- tcp\_server.c   -- task 10, 11, 12: tcp\_server


## ric's flags

- n  -> Task n(hostname)                          -> Task 1
- w  -> Task w(who is it, weak nslookup)          -> Task 2
- u  -> Task udp\_client                           -> Task 3, 4, 5
- t  -> Task tcp\_client                           -> Task 6, 7, 8
- l  -> multiplexes u and t to servers
    + u  -> Task udp\_server                       -> Task 9
    + t  -> Task tcp\_server                       -> Task 10, 11, 12


## Usage

```shell
  ric is a RCI Internet Command.
  Usage: ric [OPTIONS] [HOSTNAME:PORT]
  Options:
     - h          -- display help and exit
     - v          -- display version and exit
     - n          -- hostname: Task 1
     - w          -- nslookup: Task 2
     - u          -- udp_client: Task 3, 4, 5
     - t          -- tcp_client: Task 6, 7, 8
     - l          -- multiplexes u and t to servers
       + u        -- udp_server: Task 9
       + t        -- tcp_server: Task 10, 11, 12
  Default values:
    Host: tejo.tecnico.ulisboa.pt
    Port: 58001
```


## Recommended stuff

For students of RCI.

Some code, as you learn by coding, analysing and copying:
  - suckless tools, small and awesome:
    + ii     - IRC client  -- http://tools.suckless.org/ii/
    + quark  - HTTP server -- http://tools.suckless.org/quark/
    + sic    - IRC client  -- http://tools.suckless.org/sic/
  - calcurse - Curses Calendar -- https://www.calcurse.org/


## LICENSE

MIT License

Copyright (c) 2020 Carlos Pinto Machado, Mariana Carvalho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

