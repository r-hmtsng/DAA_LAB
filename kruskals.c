#include <stdio.h>
#include <stdlib.h>

struct edge
{
    int u, v, cost;
};

typedef struct edge edge;

int find(int v, int parent[])
{
    while (parent[v] != v)
    {
        v = parent[v];
    }
    return v;
}

void union_ij(int i, int j, int parent[])
{
    if (i < j)
        parent[j] = i;
    else
        parent[i] = j;
}

int compare(const void *a, const void *b)
{
    return ((edge *)a)->cost - ((edge *)b)->cost;
}

void kruskal(int n, int graph[][n])
{
    int count, i, sum = 0;
    int parent[n];
    edge e[n * n];

    for (i = 0; i < n; i++)
    {
        parent[i] = i;
    }

    int m = 0;
    for (i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (graph[i][j] != 0)
            {
                e[m].u = i;
                e[m].v = j;
                e[m].cost = graph[i][j];
                m++;
            }
        }
    }

    qsort(e, m, sizeof(edge), compare);

    count = 0;
    printf("The spanning tree is as follows:\n");
    for (i = 0; i < m; i++)
    {
        int u = e[i].u;
        int v = e[i].v;
        int root_u = find(u, parent);
        int root_v = find(v, parent);

        if (root_u != root_v)
        {
            printf("%d - %d\n", u, v);
            sum += e[i].cost;
            union_ij(root_u, root_v, parent);
            count++;
        }

        if (count == n - 1)
            break;
    }

    printf("The cost of the minimum spanning tree is %d\n", sum);
}

int main()
{
    int n, i, j;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int graph[n][n];
    printf("Enter the adjacency matrix (use '0' for no edge and cost otherwise):\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    kruskal(n, graph);

    return 0;
}
