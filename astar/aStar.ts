//AStar algorithm

function ArraySwapIndex<T>(arr: Array<T>, indexA: number, indexB: number) {
    [arr[indexA], arr[indexB]] = [arr[indexB], arr[indexA]];
}

//Represent each node in the search graph, has reference to its parent
// and children node.
class node {
    public parent: node|null;
    public children: node[];
    public state: number[];
    public blankIndex: number;
    public value: number;
    constructor(state: number[], currentBlank: number, parent: node|null) {
        this.parent = parent;
        this.state = Object.assign([], state);
        this.blankIndex = currentBlank;
        this.children = [];
        this.value = 0;
    }

    get identifier() {
        return this.state.toString();
    }

    public getChildren(): node[] {
        if (this.children.length !== 0) {
            return this.children
        }
        if (this.blankIndex % 3 !== 2) {
            //Blank move right
            let newState = Object.assign([], this.state);
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex+1);
            this.children.push(new node(newState, this.blankIndex + 1, this));
        }
        if (this.blankIndex % 3 !== 0) {
            //Blank move left
            let newState = Object.assign([], this.state);
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex-1);
            this.children.push(new node(newState, this.blankIndex - 1, this));
        }
        if (Math.floor(this.blankIndex / 3) !== 0) {
            //Blank move up
            let newState = Object.assign([], this.state);
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex-3);
            this.children.push(new node(newState, this.blankIndex - 3, this));
        }
        if (Math.floor(this.blankIndex / 3) !== 2) {
            //Blank move down
            let newState = Object.assign([], this.state);
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex+3);
            this.children.push(new node(newState, this.blankIndex + 3, this));
        }
        return this.children;
    }
}


abstract class searchMethod {
    public openTable: node[];
    public closedTable: {[id:string]: node};

    public currentNode: node;
    //The path from initial node to the current node
    private totalStep: number;

    constructor(initState: number[], currentBlank: number) {
        this.openTable = [];
        this.closedTable = {};
        this.currentNode = new node(initState, currentBlank, null);
        this.openTable.push(this.currentNode);
        this.next();
        this.totalStep = 0;
    }

    public next(): [number[], number] {
        if (this.checkResult(this.currentNode.state)) {
            return [this.currentNode.state, this.currentNode.blankIndex];
        }
        this.totalStep++;
        let [newNode, index] = this.getLowestNode();
        while (newNode.identifier in this.closedTable) {
            this.openTable.splice(index, 1);
            [newNode, index] = this.getLowestNode();
        }
        this.openTable.splice(index, 1);
        this.closedTable[newNode.identifier] = newNode;
        this.currentNode = newNode;
        let children = this.currentNode.getChildren();
        for (let child of children) {
            this.addNewOpenNode(child);
        }
        return [newNode.state, newNode.blankIndex];
    }

    public runAll(): any {
        while (true) {
            let [state, blank] = this.next();
            if (this.checkResult(state)) {
                break;
            }
        }
    }

    public checkResult(state: number[]): boolean {
        for (let i = 0; i < 9; i++) {
            if (state[i] !== i) {
                return false;
            }
        }
        return true;
    }

    public get pathToCurrent(): node[] {
        let result: node[] = [];
        let curr: node|null = this.currentNode;
        while (curr !== null) {
            result.unshift(curr);
            curr = curr.parent;
        }
        return result;
    }

    public get steps() { return this.totalStep; }

    //Returns node and index of the node in open table
    public abstract getLowestNode(): [node, number];

    public abstract addNewOpenNode(newNode: node): void;

}

class aStarH1 extends searchMethod{

    public getLowestNode(): [node, number] {
        return [this.openTable[0], 0];
    }

    public addNewOpenNode(newNode: node): void {
        this.openTable.push(newNode);
    }
}

class aStarH2 extends searchMethod{

    public getLowestNode(): [node, number] {
        return [this.openTable[0], 0];
    }

    public addNewOpenNode(newNode: node): void {
        this.openTable.push(newNode);
    }
}

class bfs extends searchMethod {

    public getLowestNode(): [node, number] {
        return [this.openTable[0], 0];
    }

    public addNewOpenNode(newNode: node): void {
        if (!(newNode.identifier in this.closedTable)) {
            this.openTable.push(newNode);
        }
    }
}

