# Social Network Analyzer

A social network platform combining a C++ graph engine with a Flask REST API and a browser-based dashboard. It models users as nodes and friendships as edges, and implements core graph algorithms — BFS, DFS, shortest path, and mutual-friend-based recommendations — with both a CLI and a web interface.

## Features

- **User management** — add, remove, search, and display users.
- **Friendship graph** — add/remove friendships, check mutual connections.
- **Graph algorithms** — BFS, DFS, shortest path (unweighted, via BFS), and friend recommendations based on mutual connections.
- **Persistence** — users and friendships saved to/loaded from text files.
- **REST API (Flask)** — exposes the network over HTTP: add users/friendships, fetch users, graph data, dashboard stats, and recommendations.
- **Web dashboard** — HTML/CSS/JS frontend with:
  - **Dashboard** — live stats (user count, friendship count, most connected user, etc.)
  - **Users** — add, view, search, and delete users
  - **Graph** — interactive graph visualization (Cytoscape.js) with BFS/DFS/shortest path highlighting and friend recommendations

## Project structure

social-network-analyzer/
├── include/ # C++ headers
│ ├── SocialGraph.h
│ └── User.h
├── src/ # C++ source
│ ├── main.cpp
│ ├── SocialGraph.cpp
│ └── User.cpp
├── backend/ # Flask REST API
│ └── app.py
├── frontend/ # Web dashboard
│ ├── index.html
│ ├── users.html
│ ├── graph.html
│ └── style.css
├── data/ # Runtime-generated persistence (users.txt, friendships.txt)
├── .gitignore
├── README.md
└── social.exe


> **Note:** This project currently has hardcoded absolute file paths (e.g. `D:/DSA Projects/Social Network/...`) in `main.cpp`, `SocialGraph.cpp`, `User.cpp`, and `app.py`. These need to be updated to relative paths for the project to build/run correctly outside the original machine/folder setup.

## Building the C++ CLI

Requires a C++ compiler with C++11 support or later.

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o social_network
```

Run it:

```bash
./social_network
```

Menu-driven CLI supporting: add user, add friendship, show users/friends, BFS, DFS, shortest path, friend recommendations, search, mutual friends count, remove user/friendship, and save/load network.

## Running the web app (Flask + dashboard)

1. Install dependencies:
```bash
   pip install flask flask-cors
```
2. Run the backend:
```bash
   python backend/app.py
```
   This starts the Flask server on `http://127.0.0.1:5000`.
3. Open `frontend/index.html` in your browser (the dashboard fetches data from the Flask API).

### API Endpoints

| Method | Endpoint | Description |
|---|---|---|
| POST | `/add_user` | Add a new user |
| DELETE | `/delete_user/<id>` | Delete a user |
| POST | `/add_friendship` | Add a friendship between two users |
| POST | `/remove_friendship` | Remove a friendship |
| GET | `/get_users` | List all users |
| GET | `/get_graph` | Get graph data (nodes + edges) for visualization |
| GET | `/dashboard_stats` | Get summary stats (user/friendship counts, etc.) |
| GET | `/recommend/<user_id>` | Get friend recommendations for a user |

## How recommendations work

Friend recommendations are based on **mutual connections**: for a given user, the algorithm looks at friends-of-friends who aren't already friends with the user, and ranks them by how many mutual friends they share.

## Persistence

- Users: `id,name,age,city` per line.
- Friendships: `user1,user2` per line (one direction only; treated as undirected).

## License

Personal / educational project.