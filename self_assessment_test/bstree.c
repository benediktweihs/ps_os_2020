
// Authors: Benedikt Weihs, Tappeiner Thomas, Bänsch David
#include "bstree.h"
#include "assert.h"
#include "limits.h"

typedef struct bstree_node
{
    struct bstree_node * l;
    struct bstree_node * r;
    int value;
} bstree_node;

struct bstree
{
    size_t size;
    bstree_node * groot;
};

bstree *
bstree_create()
{
    bstree * tree = malloc( sizeof( bstree ) );
    tree->size = 0;
    tree->groot = NULL;
    return tree;
}

// Returns the pointer to the hypothetical node
static bstree_node **
bstree_find_parent_node_ptr( const bstree * t, int d )
{
    bstree_node ** node = ( bstree_node ** ) &( t->groot );

    if( !( *node ) )
        return NULL;
    while( ( *node )->value != d )
    {
        if( ( *node )->value > d )
        {
            if( !( ( *node )->l ) )
                return node;

            node = &( ( *node )->l );
        }
        else
        {
            if( !( ( *node )->r ) )
                return node;

            node = &( ( *node )->r );
        }
    }
    return node;
}

static bstree_node **
bstree_find_node_ptr( const bstree * t, int d )
{
    bstree_node ** parent = bstree_find_parent_node_ptr( t, d );
    if( !parent )
        return NULL;
    if( ( *parent )->value > d )
        return &( *parent )->l;
    if( ( *parent )->value < d )
        return &( *parent )->r;
    return parent;
}

void
bstree_insert( bstree * t, int d )
{
    bstree_node ** node = NULL;
    if( t->groot )
    {
        node = bstree_find_node_ptr( t, d );
        if( *node )
            return;
    }
    else
    {
        node = &( t->groot );
    }
    *node = malloc( sizeof( bstree_node ) );
    ( *node )->l = ( *node )->r = NULL;
    ( *node )->value = d;
    t->size++;
}

void
bstree_remove( bstree * t, int d )
{
    bstree_node ** parent = NULL;

    if( d == t->groot->value )
    {
        parent = &( t->groot );
    }
    else
    {
        parent = bstree_find_parent_node_ptr( t, d );
    }

    if( !parent || !( *parent ) )
        return;

    bstree_node * node_to_rm = *parent;

    // Was the element in the tree?
    if( node_to_rm->value != d )
        return;

    if( !( node_to_rm->l ) )
    {
        *parent = node_to_rm->r;
        goto free;
    }

    // find node to replace node_to_rm with:
    bstree_node * candidate = node_to_rm->l;
    while( candidate->r )
        candidate = candidate->r;
    bstree_node ** papa_candidate =
        bstree_find_parent_node_ptr( t, candidate->value );
    *papa_candidate = candidate->l;

    *parent = candidate;
    candidate->l = node_to_rm->l;
    candidate->r = node_to_rm->r;

free:
    free( node_to_rm );
    t->size--;
}

int
bstree_minimum( const bstree * t )
{
    bstree_node ** node = bstree_find_parent_node_ptr( t, INT_MIN );
    if( !node || !( *node ) )
        return 0;
    return ( *node )->value;
}

int
bstree_maximum( const bstree * t )
{
    const bstree_node * n = t->groot;
    while( n->r )
        n = n->r;
    return n->value;
}

void
bstree_destroy( bstree * t )
{
    bstree_node * node;
    while( node = t->groot, node )
    {
        bstree_remove( t, node->value );
    }
}

bool
bstree_contains( const bstree * t, int d )
{
    bstree_node ** node = bstree_find_node_ptr( t, d );
    if( !node || !( *node ) )
        return false;
    return ( *node )->value == d;
}

size_t
bstree_size( const bstree * t )
{
    return t->size;
}

void
bstree_print_nodes( const bstree_node * t, FILE * out )
{
    fprintf( out, "(" );
    if( t->l )
    {
        bstree_print_nodes( t->l, out );
        fprintf( out, ", " );
    }
    fprintf( out, "%i", t->value );
    if( t->r )
    {
        fprintf( out, ", " );
        bstree_print_nodes( t->r, out );
    }
    fprintf( out, ")" );
}

void
bstree_print( const bstree * t, FILE * out )
{
    if( t->groot )
        bstree_print_nodes( t->groot, out );
    else
        fprintf( out, "( NIL )" );
    fprintf( out, " : %zu\n", t->size );
}

