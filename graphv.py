import networkx as nx
import matplotlib.pyplot as plt
import pandas as pd

# Baca hasil dari CSV
data = pd.read_csv("adt/hasil_dijkstra.csv")

# Buat graf
G = nx.DiGraph()  # Gunakan DiGraph untuk graf berarah
for _, row in data.iterrows():
    if row['Jarak Ke'] != -1:  # Abaikan simpul yang tidak terhubung
        G.add_edge(row['Simpul Awal'], row['Simpul Tujuan'], weight=row['Jarak Ke'])

# Tentukan posisi simpul (opsional, untuk tata letak yang lebih rapi)
pos = nx.spring_layout(G)

# Visualisasi graf
plt.figure(figsize=(8, 6))
nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=2000, font_size=10)
labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
plt.title("Visualisasi Hasil Dijkstra")
plt.show()