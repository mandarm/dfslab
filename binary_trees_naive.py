def preorder(T) :
    if T == None: return
    print(T['data'], end=" ")
    preorder(T['left'])
    preorder(T['right'])

def inorder(T) :
    if T == None: return
    inorder(T['left'])
    print(T['data'], end=" ")
    inorder(T['right'])

if __name__ == '__main__':
    root = {'data': 0,
            'left': None,
            'right': None, 
            'parent': None}

    root['left'] = {'data': 1, 'left': None, 'right': None, 'parent': root}
    root['right'] = {'data': 2, 'left': None, 'right': None, 'parent': root}

    l = root['left']
    l['left'] = {'data': 3, 'left': None, 'right': None, 'parent': l}

    r = root['right']
    r['left'] = {'data': 4, 'left': None, 'right': None, 'parent': r}
    r['right'] = {'data': 5, 'left': None, 'right': None, 'parent': r}

    x = r['left']
    x['left'] = {'data': 6, 'left': None, 'right': None, 'parent': x}
    x['right'] = {'data': 7, 'left': None, 'right': None, 'parent': x}

    print("Preorder: ", end="")
    preorder(root)
    print()

    print("Inorder: ", end="")
    inorder(root)
    print()
