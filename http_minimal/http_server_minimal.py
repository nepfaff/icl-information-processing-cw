# IMPORTANT: Requires python3.6 instead of python3 command to run
# Could use python3 if using assignment rather than "with socketserver" statement

import http.server
import socketserver

PORT = 8000
Handler = http.server.SimpleHTTPRequestHandler

with socketserver.TCPServer(("127.0.0.1", PORT), Handler) as httpd:
    print("serving at port", PORT)
    httpd.serve_forever()
