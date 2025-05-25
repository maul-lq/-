import networkx as nx
import matplotlib.pyplot as plt

# Definisikan adjacency matrix
adjacency_matrix = [
    [0, 5, 0, 2, 0],
    [6, 0, 3, 0, 0],
    [0, 0, 0, 0, 9],
    [0, 0, 12, 0, 7],
    [0, 14, 0, 0, 0]
]

# Buat graf menggunakan NetworkX
G = nx.DiGraph()  # Directed graph

# Tambahkan simpul dan hubungan berdasarkan adjacency matrix
for i in range(len(adjacency_matrix)):
    for j in range(len(adjacency_matrix[i])):
        if adjacency_matrix[i][j] != 0:
            G.add_edge(i + 1, j + 1, weight=adjacency_matrix[i][j])

# Posisi simpul untuk tata letak graf
pos = nx.spring_layout(G)

# Gambarkan graf
plt.figure(figsize=(8, 6))
nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=2000, font_size=10, font_weight='bold', arrowsize=20)
labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=labels, font_size=10)

# Tampilkan plot
plt.title("Visualisasi Graf")
plt.show()