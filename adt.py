import networkx as nx
import matplotlib.pyplot as plt

# Definisikan adjacency matrix
adjacency_matrix = [
    [0, 3, 0, 3, 3, 0],
    [3, 0, 0, 0, 0, 6],
    [0, 0, 0, 0, 0, 7],
    [3, 0, 0, 0, 0, 0],
    [3, 0, 0, 0, 0, 0],
    [0, 6, 7, 0, 0, 0],
]

# Buat graf menggunakan NetworkX
G = nx.DiGraph()

# Tambahkan simpul dan edge berdasarkan adjacency matrix
for i in range(len(adjacency_matrix)):
    for j in range(len(adjacency_matrix[i])):
        if adjacency_matrix[i][j] != 0:
            G.add_edge(i + 1, j + 1, weight=adjacency_matrix[i][j])

# Atur posisi dengan spring_layout (sesuaikan parameter agar tampilan tidak terlalu berdesakan)
pos = nx.spring_layout(G, k=4, seed=42)

# Gambarkan graf
plt.figure(figsize=(5, 5))
nx.draw(
    G,
    pos,
    with_labels=True,
    node_color='lightblue',
    node_size=2500,
    font_size=12,
    font_weight='bold',
    arrowsize=20,
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

nx.draw_networkx_edge_labels(G, pos, edge_labels=combined_labels, font_size=10)

plt.title("Visualisasi Graf (Edge dengan Bobot Gabungan)", fontsize=16)
plt.show()