from flask import Flask, request, jsonify
from flask_cors import CORS

app = Flask(__name__)

CORS(app)

@app.route("/add_user", methods=["POST"])
def add_user():

    data = request.json

    print("Received:", data)

    user_id = data["id"]
    name = data["name"]
    age = data["age"]
    city = data["city"]

    import os

    print(
        os.path.abspath(
            "D:/DSA Projects/Social Network/users.txt"
        )
    )

    with open(
        "D:/DSA Projects/Social Network/users.txt",
        "a"
    ) as f:

        f.write(
            f"{user_id},{name},{age},{city}\n"
        )

    return jsonify({
        "message":
        "User Saved Successfully"
    })

@app.route(
    "/add_friendship",
    methods=["POST"]
)
def add_friendship():

    data = request.json

    user1 = data["user1"]
    user2 = data["user2"]

    with open(
        r"D:\DSA Projects\Social Network\friendships.txt",
        "a"
    ) as f:

        f.write(
            f"{user1},{user2}\n"
        )

    return jsonify({
        "message":
        "Friendship Saved"
    })

@app.route("/get_users", methods=["GET"])
def get_users():

    users = []

    with open(
        r"D:\DSA Projects\Social Network\users.txt",
        "r"
    ) as f:

        for line in f:

            line = line.strip()

            if not line:
                continue

            parts = line.split(",")

            users.append({
                "id": parts[0],
                "name": parts[1],
                "age": parts[2],
                "city": parts[3]
            })

    return jsonify(users)

@app.route("/dashboard_stats", methods=["GET"])
def dashboard_stats():

    users = 0

    with open(
        r"D:\DSA Projects\Social Network\users.txt",
        "r"
    ) as f:

        for line in f:
            if line.strip():
                users += 1

    friendships = 0

    try:
        with open(
            r"D:\DSA Projects\Social Network\friendships.txt",
            "r"
        ) as f:

            for line in f:
                if line.strip():
                    friendships += 1
    except:
        friendships = 0

    return jsonify({
        "users": users,
        "friendships": friendships,
        "recommendations": 0,
        "most_connected": "Gaurav",
        "components": 1,
        "average_friends": round(friendships * 2 / max(users,1), 2)
    })

@app.route("/get_graph", methods=["GET"])
def get_graph():

    users = []
    edges = []

    with open(
        r"D:\DSA Projects\Social Network\users.txt",
        "r"
    ) as f:

        for line in f:

            line = line.strip()

            if not line:
                continue

            parts = line.split(",")

            users.append({
                "id": parts[0],
                "label": parts[1]
            })

    try:

        with open(
            r"D:\DSA Projects\Social Network\friendships.txt",
            "r"
        ) as f:

            for line in f:

                line = line.strip()

                if not line:
                    continue

                parts = line.split(",")

                edges.append({
                    "source": parts[0],
                    "target": parts[1]
                })

    except:
        pass

    return jsonify({
        "users": users,
        "edges": edges
    })

@app.route("/recommend/<user_id>", methods=["GET"])
def recommend(user_id):

    graph = {}

    with open(
        r"D:\DSA Projects\Social Network\friendships.txt",
        "r"
    ) as f:

        for line in f:

            line = line.strip()

            if not line:
                continue

            u,v = line.split(",")

            graph.setdefault(u,set()).add(v)
            graph.setdefault(v,set()).add(u)

    if user_id not in graph:
        return jsonify([])

    friends = graph[user_id]

    users = {}

    with open(
        r"D:\DSA Projects\Social Network\users.txt",
        "r"
    ) as f:

        for line in f:

            line = line.strip()

            if not line:
                continue

            parts = line.split(",")

            users[parts[0]] = parts[1]

    recommendations = {}

    for friend in friends:

        for candidate in graph.get(friend,set()):

            if candidate == user_id:
                continue

            if candidate in friends:
                continue

            recommendations[candidate] = \
            recommendations.get(candidate,0) + 1

    result = []

    for user,count in recommendations.items():

        result.append({
            "id": user,
            "name": users.get(user,"Unknown"),
            "mutual": count
        })

    result.sort(
        key=lambda x:x["mutual"],
        reverse=True
    )

    return jsonify(result)

@app.route(
"/delete_user/<user_id>",
methods=["DELETE"]
)
def delete_user(user_id):

    users = []

    with open(
    r"D:\DSA Projects\Social Network\users.txt",
    "r"
    ) as f:

        for line in f:

            if not line.startswith(
                user_id + ","
            ):
                users.append(line)

    with open(
    r"D:\DSA Projects\Social Network\users.txt",
    "w"
    ) as f:

        f.writelines(users)

    return jsonify({
        "message":
        "User Deleted"
    })

@app.route(
"/remove_friendship",
methods=["POST"]
)
def remove_friendship():

    data = request.json

    user1 = data["user1"]
    user2 = data["user2"]

    friendships = []

    with open(
    r"D:\DSA Projects\Social Network\friendships.txt",
    "r"
    ) as f:

        for line in f:

            u,v = line.strip().split(",")

            if (
                (u==user1 and v==user2)
                or
                (u==user2 and v==user1)
               ):
                continue

            friendships.append(line)

    with open(
    r"D:\DSA Projects\Social Network\friendships.txt",
    "w"
    ) as f:

        f.writelines(friendships)

    return jsonify({
        "message":
        "Friendship Removed"
    })

if __name__ == "__main__":
    app.run(debug=True)
