# Mini-Google

A lightweight local search engine implemented in C using raw sockets and POSIX threads. It runs a simple multithreaded HTTP server that allows users to search for keywords inside text files stored in a `data/` directory.

## Features

- Local web server on `localhost:8080`
- Search through `.txt` files in `data/`
- Caching of previous queries using `cache/`
- HTML templating for output using `result_template.html`
- Logs suspicious input in `logs/security.log`
- Input sanitization to prevent XSS and path traversal
- Fully multithreaded (one thread per request)

## File Structure

mini-google/
├── main.c
├── server.c / server.h
├── search.c / search.h
├── file_saver.c / file_saver.h
├── template.c / template.h
├── security.c / security.h
├── Makefile
├── .gitignore
├── data/                 # .txt files to search
├── cache/                # cached results (autocreated)
├── logs/security.log     # security log (autocreated)
└── html/
    ├── index.html
    └── result_template.html

## How to Run

1. Clone or download the project:

   git clone <your_repo_url>
   cd mini-google

2. Build the project:

   make

3. Start the server:

   ./mini-google

You should see:

   🌐 Listening on http://localhost:8080

## Usage

1. Open a browser and go to http://localhost:8080
2. Enter a search query (e.g. "hello")
3. The server searches all `.txt` files in `data/` for matches
4. Results are shown in a templated HTML page

## Development Notes

- All queries are sanitized before use
- Cached results are saved in `cache/` using `<query>.html` filenames
- HTML templates are plain text files with `{{RESULTS}}` placeholder
- Logs are appended to `logs/security.log` when suspicious inputs are detected

## Troubleshooting

❌ Browser says “Connection reset by peer”

- Make sure the server is running
- Try `curl http://localhost:8080` in terminal
- If you're on WSL, open `http://<hostname -I>:8080` in the browser
- Disable firewall or antivirus that may be blocking port 8080

## License

MIT License (optional — add your own if needed)
