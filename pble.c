/* PBLE 2: Campus Shortest Route Finder - Dijkstra's Algorithm
   Time complexity: O(V^2) - V iterations, each with an O(V) search and O(V) relaxation */
#include <stdio.h>
#include <string.h>
#define MAX 20
#define INF 9999

int n = 0, source = -1, done = 0;
int g[MAX][MAX], dist[MAX], parent[MAX], visited[MAX];
char name[MAX][40];

void enterGraph() {
    int i, j, roads, u, v, w;
    printf("Number of locations: ");
    scanf("%d", &n);
    if (n < 2 || n > MAX) { n = 0; printf("Invalid number.\n"); return; }
    for (i = 0; i < n; i++) {
        printf("Name of location %d: ", i + 1);
        scanf(" %39[^\n]", name[i]);
    }
    for (i = 0; i < n; i++)                 /* 0 on diagonal, INF = no road */
        for (j = 0; j < n; j++)
            g[i][j] = (i == j) ? 0 : INF;
    printf("Number of roads: ");
    scanf("%d", &roads);
    for (i = 0; i < roads; i++) {
        printf("Road %d (from to distance): ", i + 1);
        scanf("%d %d %d", &u, &v, &w);
        if (u < 1 || u > n || v < 1 || v > n || w < 0) {
            printf("Invalid road, re-enter.\n");
            i--;
        } else
            g[u - 1][v - 1] = g[v - 1][u - 1] = w;   /* two-way road */
    }
    source = -1;
    done = 0;
}

void showMatrix() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            if (g[i][j] == INF) printf("%6s", "INF");
            else                printf("%6d", g[i][j]);
        printf("   %s\n", name[i]);
    }
}

void selectSource() {
    int i, s;
    for (i = 0; i < n; i++) printf("%d. %s\n", i + 1, name[i]);
    printf("Enter source number: ");
    scanf("%d", &s);
    if (s < 1 || s > n) { printf("Invalid source.\n"); return; }
    source = s - 1;
    done = 0;
    printf("Source: %s\n", name[source]);
}

void dijkstra() {
    int i, count, u, v, min;
    for (i = 0; i < n; i++) { dist[i] = INF; parent[i] = -1; visited[i] = 0; }
    dist[source] = 0;
    for (count = 0; count < n; count++) {
        u = -1; min = INF;                  /* nearest unvisited vertex */
        for (i = 0; i < n; i++)
            if (!visited[i] && dist[i] < min) { min = dist[i]; u = i; }
        if (u == -1) break;                 /* rest are unreachable */
        visited[u] = 1;
        for (v = 0; v < n; v++)             /* relax edges of u */
            if (!visited[v] && g[u][v] != INF && dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v];
                parent[v] = u;
            }
        printf("Visit %-20s dist:", name[u]);   /* intermediate result */
        for (i = 0; i < n; i++)
            if (dist[i] == INF) printf("%5s", "INF");
            else                printf("%5d", dist[i]);
        printf("\n");
    }
    done = 1;
}

void printPath(int v) {                     /* follow parent[] back to source */
    if (parent[v] != -1) { printPath(parent[v]); printf(" -> "); }
    printf("%s", name[v]);
}

void showPaths() {
    int i;
    printf("%-22s%-10s%s\n", "Destination", "Distance", "Shortest Path");
    for (i = 0; i < n; i++) {
        if (i == source) continue;
        if (dist[i] == INF) { printf("%-22sINF       No path\n", name[i]); continue; }
        printf("%-22s%-10d", name[i], dist[i]);
        printPath(i);
        printf("\n");
    }
}

void showDistances() {
    int i;
    for (i = 0; i < n; i++)
        printf("%-22s%d\n", name[i], dist[i]);
}

int main() {
    int choice;
    do {
        printf("\n1. Enter Campus Graph\n2. Display Adjacency Matrix\n3. Select Source Location\n"
               "4. Find Shortest Distance\n5. Display Shortest Paths\n"
               "6. Display Distance from Source to All Locations\n7. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); choice = 0; }

        if (choice >= 2 && choice <= 4 && n == 0)  printf("Enter the graph first.\n");
        else if (choice == 4 && source < 0)        printf("Select a source first.\n");
        else if ((choice == 5 || choice == 6) && !done) printf("Run option 4 first.\n");
        else switch (choice) {
            case 1: enterGraph();     break;
            case 2: showMatrix();     break;
            case 3: selectSource();   break;
            case 4: dijkstra();       break;
            case 5: showPaths();      break;
            case 6: showDistances();  break;
            case 7: printf("Goodbye!\n"); break;
            default: printf("Invalid choice! Enter 1-7.\n");
        }
    } while (choice != 7);
    return 0;
}
