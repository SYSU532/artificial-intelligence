
//AStar algorithm
/// <reference path="./priority-queue.d.ts" />

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
        this.state = state.slice();
        this.blankIndex = currentBlank;
        this.children = [];
        this.value = 0;
    }

    public get identifier() {
        return this.state.toString();
    }

    public get path(): node[] {
        let result: node[] = [];
        let curr: node|null = this;
        while (curr !== null) {
            result.unshift(curr);
            curr = curr.parent;
        }
        return result;
    }

    public getChildren(): node[] {
        if (this.children.length !== 0) {
            return this.children
        }
        if (this.blankIndex % 3 !== 2) {
            //Blank move right
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex+1);
            this.children.push(new node(newState, this.blankIndex + 1, this));
        }
        if (this.blankIndex % 3 !== 0) {
            //Blank move left
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex-1);
            this.children.push(new node(newState, this.blankIndex - 1, this));
        }
        if (Math.floor(this.blankIndex / 3) !== 0) {
            //Blank move up
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex-3);
            this.children.push(new node(newState, this.blankIndex - 3, this));
        }
        if (Math.floor(this.blankIndex / 3) !== 2) {
            //Blank move down
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex+3);
            this.children.push(new node(newState, this.blankIndex + 3, this));
        }
        return this.children;
    }
}


abstract class searchMethod {
    public openTable: PriorityQueue<node>;
    public closedTable: {[id:string]: node};

    public currentNode: node;
    //The path from initial node to the current node
    private totalStep: number;

    constructor(initState: number[], currentBlank: number) {
        this.openTable = new PriorityQueue<node>({
            comparator: function (a:node, b:node) {
                return a.value - b.value;
            },
        });
        this.closedTable = {};
        this.currentNode = new node(initState, currentBlank, null);
        this.openTable.queue(this.currentNode);
        this.next();
        this.totalStep = 0;
    }

    public next(): [number[], number] {
        if (this.checkResult(this.currentNode.state)) {
            return [this.currentNode.state, this.currentNode.blankIndex];
        }
        this.totalStep++;
        if (this.openTable.length === 0) {
            alert("搜索失败");
            throw "Empty open table";
        }
        let newNode = this.openTable.peek();
        while ((newNode).identifier in this.closedTable) {
            this.openTable.dequeue();
            if (this.openTable.length === 0) {
                alert("搜索失败");
                throw "Empty open table";
            }
            newNode = this.openTable.peek();
        }
        this.openTable.dequeue();
        this.closedTable[newNode.identifier] = newNode;
        this.currentNode = newNode;
        let children = this.currentNode.getChildren();
        for (let child of children) {
            this.addNewOpenNodeWithVal(child);
        }
        return [newNode.state, newNode.blankIndex];
    }

    public getLowestNode() : node|undefined {
        return this.openTable.peek();
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
        return this.currentNode.path;
    }

    public get steps() { return this.totalStep; }

    public abstract addNewOpenNodeWithVal(newNode: node): void;

}

class aStarH1 extends searchMethod{

    public addNewOpenNodeWithVal(newNode: node): void {
        this.openTable.queue(newNode);
    }
}

class aStarH2 extends searchMethod{

    public addNewOpenNodeWithVal(newNode: node): void {
        if (!(newNode.identifier in this.closedTable)) {
            this.openTable.queue(newNode);
        }
    }
}

class bfs extends searchMethod {

    public addNewOpenNodeWithVal(newNode: node): void {
        if (!(newNode.identifier in this.closedTable)) {
            newNode.value = (<node>newNode.parent).value + 1;
            this.openTable.queue(newNode);
        }
    }
}



