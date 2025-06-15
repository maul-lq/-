import networkx as nx
import matplotlib.pyplot as plt
import random

# Generate a 50x50 adjacency matrix with random weights
random.seed(42)  # For reproducible results
size = 50
adjacency_matrix = []

for i in range(size):
    row = []
    for j in range(size):
        if i == j:
            row.append(0)  # No self-loops
        elif random.random() < 0.1:  # 10% chance of connection
            row.append(random.randint(1, 10))  # Random weight 1-10
        else:
            row.append(0)
    adjacency_matrix.append(row)

print(adjacency_matrix)

# Buat graf menggunakan NetworkX
G = nx.DiGraph()

# Tambahkan simpul dan edge berdasarkan adjacency matrix
for i in range(len(adjacency_matrix)):
    for j in range(len(adjacency_matrix[i])):
        if adjacency_matrix[i][j] != 0:
            G.add_edge(i + 1, j + 1, weight=adjacency_matrix[i][j])

# Atur posisi dengan spring_layout (sesuaikan parameter agar tampilan tidak terlalu berdesakan)
pos = nx.spring_layout(G, k=8, iterations=50, seed=42)

# Gambarkan graf
plt.figure(figsize=(15, 15))
nx.draw(
    G,
    pos,
    with_labels=True,
    node_color='lightblue',
    node_size=300,
    font_size=6,
    font_weight='bold',
    arrowsize=10,
    edge_color='gray',
    alpha=0.7,
)

# Buat dictionary untuk label edge dan gabungkan weight untuk edge yang berlawanan
combined_labels = {}
processed = set()

for u, v, data in G.edges(data=True):
    if (v, u) in G.edges() and ((v, u) not in processed):
        new_weight = data['weight'] + G[v][u]['weight']
        combined_labels[(u, v)] = new_weight
        processed.add((u, v))
        processed.add((v, u))
    elif (u, v) not in processed:
        combined_labels[(u, v)] = data['weight']

nx.draw_networkx_edge_labels(G, pos, edge_labels=combined_labels, font_size=4)

plt.title("Visualisasi Graf 50x50 (Edge dengan Bobot Gabungan)", fontsize=16)
plt.show()