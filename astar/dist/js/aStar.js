"use strict";
//AStar algorithm
/// <reference path="./priority-queue.d.ts" />
function ArraySwapIndex(arr, indexA, indexB) {
    [arr[indexA], arr[indexB]] = [arr[indexB], arr[indexA]];
}
//Represent each node in the search graph, has reference to its parent
// and children node.
class node {
    constructor(state, currentBlank, parent) {
        this.parent = parent;
        this.state = state.slice();
        this.blankIndex = currentBlank;
        this.children = [];
        this.value = 0;
    }
    get identifier() {
        return this.state.toString();
    }
    get path() {
        let result = [];
        let curr = this;
        while (curr !== null) {
            result.unshift(curr);
            curr = curr.parent;
        }
        return result;
    }
    getChildren() {
        if (this.children.length !== 0) {
            return this.children;
        }
        if (this.blankIndex % 3 !== 2) {
            //Blank move right
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex + 1);
            this.children.push(new node(newState, this.blankIndex + 1, this));
        }
        if (this.blankIndex % 3 !== 0) {
            //Blank move left
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex - 1);
            this.children.push(new node(newState, this.blankIndex - 1, this));
        }
        if (Math.floor(this.blankIndex / 3) !== 0) {
            //Blank move up
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex - 3);
            this.children.push(new node(newState, this.blankIndex - 3, this));
        }
        if (Math.floor(this.blankIndex / 3) !== 2) {
            //Blank move down
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex + 3);
            this.children.push(new node(newState, this.blankIndex + 3, this));
        }
        return this.children;
    }
}
class searchMethod {
    constructor(initState, currentBlank) {
        this.openTable = new PriorityQueue({
            comparator: function (a, b) {
                return a.value - b.value;
            },
        });
        this.closedTable = {};
        this.currentNode = new node(initState, currentBlank, null);
        this.openTable.queue(this.currentNode);
        this.next();
        this.totalStep = 0;
    }
    next() {
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
    getLowestNode() {
        return this.openTable.peek();
    }
    runAll() {
        while (true) {
            let [state, blank] = this.next();
            if (this.checkResult(state)) {
                break;
            }
        }
    }
    checkResult(state) {
        for (let i = 0; i < 9; i++) {
            if (state[i] !== i) {
                return false;
            }
        }
        return true;
    }
    get pathToCurrent() {
        return this.currentNode.path;
    }
    get steps() { return this.totalStep; }
}
class aStarH1 extends searchMethod {
    addNewOpenNodeWithVal(newNode) {
        if (!(newNode.identifier in this.closedTable)) {
            //The cost from root to the current node, i.e g*(n)
            let currentCost = newNode.path.length;
            //The cost from current node to destination(h1*(n)) is estimated
            //by the distance of each misplaced number to its actual position.
            let estimatedMinCost = 0;
            for (let i = 0; i < newNode.state.length; i++) {
                if (newNode.state[i] !== i) {
                    estimatedMinCost++;
                }
            }
            newNode.value = currentCost + estimatedMinCost - 1;
            this.openTable.queue(newNode);
        }
    }
}
class aStarH2 extends searchMethod {
    addNewOpenNodeWithVal(newNode) {
        if (!(newNode.identifier in this.closedTable)) {
            //The cost from root to the current node, i.e g*(n)
            let currentCost = newNode.path.length;
            //The cost from current node to destination(h1*(n)) is estimated
            //by the sum of the column and row differences in each misplaced position.
            let estimatedMinCost = 0;
            for (let i = 0; i < newNode.state.length; i++) {
                //Row differences
                estimatedMinCost += Math.abs(i / 3 - newNode.state[i] / 3);
                //Column differences
                estimatedMinCost += Math.abs(i % 3 - newNode.state[i] % 3);
            }
            newNode.value = currentCost + estimatedMinCost;
            this.openTable.queue(newNode);
        }
    }
}
class bfs extends searchMethod {
    addNewOpenNodeWithVal(newNode) {
        if (!(newNode.identifier in this.closedTable)) {
            newNode.value = newNode.parent.value + 1;
            this.openTable.queue(newNode);
        }
    }
}
//# sourceMappingURL=data:application/json;base64,eyJ2ZXJzaW9uIjozLCJmaWxlIjoiYVN0YXIuanMiLCJzb3VyY2VSb290IjoiIiwic291cmNlcyI6WyIuLi8uLi9zcmMvYVN0YXIudHMiXSwibmFtZXMiOltdLCJtYXBwaW5ncyI6IjtBQUNBLGlCQUFpQjtBQUNqQiw4Q0FBOEM7QUFFOUMsU0FBUyxjQUFjLENBQUksR0FBYSxFQUFFLE1BQWMsRUFBRSxNQUFjO0lBQ3BFLENBQUMsR0FBRyxDQUFDLE1BQU0sQ0FBQyxFQUFFLEdBQUcsQ0FBQyxNQUFNLENBQUMsQ0FBQyxHQUFHLENBQUMsR0FBRyxDQUFDLE1BQU0sQ0FBQyxFQUFFLEdBQUcsQ0FBQyxNQUFNLENBQUMsQ0FBQyxDQUFDO0FBQzVELENBQUM7QUFFRCxzRUFBc0U7QUFDdEUscUJBQXFCO0FBQ3JCLE1BQU0sSUFBSTtJQU9OLFlBQVksS0FBZSxFQUFFLFlBQW9CLEVBQUUsTUFBaUI7UUFDaEUsSUFBSSxDQUFDLE1BQU0sR0FBRyxNQUFNLENBQUM7UUFDckIsSUFBSSxDQUFDLEtBQUssR0FBRyxLQUFLLENBQUMsS0FBSyxFQUFFLENBQUM7UUFDM0IsSUFBSSxDQUFDLFVBQVUsR0FBRyxZQUFZLENBQUM7UUFDL0IsSUFBSSxDQUFDLFFBQVEsR0FBRyxFQUFFLENBQUM7UUFDbkIsSUFBSSxDQUFDLEtBQUssR0FBRyxDQUFDLENBQUM7SUFDbkIsQ0FBQztJQUVELElBQVcsVUFBVTtRQUNqQixPQUFPLElBQUksQ0FBQyxLQUFLLENBQUMsUUFBUSxFQUFFLENBQUM7SUFDakMsQ0FBQztJQUVELElBQVcsSUFBSTtRQUNYLElBQUksTUFBTSxHQUFXLEVBQUUsQ0FBQztRQUN4QixJQUFJLElBQUksR0FBYyxJQUFJLENBQUM7UUFDM0IsT0FBTyxJQUFJLEtBQUssSUFBSSxFQUFFO1lBQ2xCLE1BQU0sQ0FBQyxPQUFPLENBQUMsSUFBSSxDQUFDLENBQUM7WUFDckIsSUFBSSxHQUFHLElBQUksQ0FBQyxNQUFNLENBQUM7U0FDdEI7UUFDRCxPQUFPLE1BQU0sQ0FBQztJQUNsQixDQUFDO0lBRU0sV0FBVztR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QUMsQ0FBQyxHQUFHLE9BQU8sQ0FBQyxLQUFLLENBQUMsQ0FBQyxDQUFDLEdBQUMsQ0FBQyxDQUFDLENBQUM7YUFDMUQ7WUFDRCxPQUFPLENBQUMsS0FBSyxHQUFHLFdBQVcsR0FBRyxnQkFBZ0IsQ0FBQztZQUUvQyxJQUFJLENBQUMsU0FBUyxDQUFDLEtBQUssQ0FBQyxPQUFPLENBQUMsQ0FBQztTQUNqQztJQUNMLENBQUM7Q0FDSjtBQUVELE1BQU0sR0FBSSxTQUFRLFlBQVk7SUFFbkIscUJBQXFCLENBQUMsT0FBYTtRQUN0QyxJQUFJLENBQUMsQ0FBQyxPQUFPLENBQUMsVUFBVSxJQUFJLElBQUksQ0FBQyxXQUFXLENBQUMsRUFBRTtZQUMzQyxPQUFPLENBQUMsS0FBSyxHQUFVLE9BQU8sQ0FBQyxNQUFPLENBQUMsS0FBSyxHQUFHLENBQUMsQ0FBQztZQUNqRCxJQUFJLENBQUMsU0FBUyxDQUFDLEtBQUssQ0FBQyxPQUFPLENBQUMsQ0FBQztTQUNqQztJQUNMLENBQUM7Q0FDSiIsInNvdXJjZXNDb250ZW50IjpbIlxuLy9BU3RhciBhbGdvcml0aG1cbi8vLyA8cmVmZXJlbmNlIHBhdGg9XCIuL3ByaW9yaXR5LXF1ZXVlLmQudHNcIiAvPlxuXG5mdW5jdGlvbiBBcnJheVN3YXBJbmRleDxUPihhcnI6IEFycmF5PFQ+LCBpbmRleEE6IG51bWJlciwgaW5kZXhCOiBudW1iZXIpIHtcbiAgICBbYXJyW2luZGV4QV0sIGFycltpbmRleEJdXSA9IFthcnJbaW5kZXhCXSwgYXJyW2luZGV4QV1dO1xufVxuXG4vL1JlcHJlc2VudCBlYWNoIG5vZGUgaW4gdGhlIHNlYXJjaCBncmFwaCwgaGFzIHJlZmVyZW5jZSB0byBpdHMgcGFyZW50XG4vLyBhbmQgY2hpbGRyZW4gbm9kZS5cbmNsYXNzIG5vZGUge1xuICAgIHB1YmxpYyBwYXJlbnQ6IG5vZGV8bnVsbDtcbiAgICBwdWJsaWMgY2hpbGRyZW46IG5vZGVbXTtcbiAgICBwdWJsaWMgc3RhdGU6IG51bWJlcltdO1xuICAgIHB1YmxpYyBibGFua0luZGV4OiBudW1iZXI7XG4gICAgLy90aGUgdmFsdWUgaXMgdGhlIGYobikgb2YgdGhlIG5vZGUuXG4gICAgcHVibGljIHZhbHVlOiBudW1iZXI7XG4gICAgY29uc3RydWN0b3Ioc3RhdGU6IG51bWJlcltdLCBjdXJyZW50Qmxhbms6IG51bWJlciwgcGFyZW50OiBub2RlfG51bGwpIHtcbiAgICAgICAgdGhpcy5wYXJlbnQgPSBwYXJlbnQ7XG4gICAgICAgIHRoaXMuc3RhdGUgPSBzdGF0ZS5zbGljZSgpO1xuICAgICAgICB0aGlzLmJsYW5rSW5kZXggPSBjdXJyZW50Qmxhbms7XG4gICAgICAgIHRoaXMuY2hpbGRyZW4gPSBbXTtcbiAgICAgICAgdGhpcy52YWx1ZSA9IDA7XG4gICAgfVxuXG4gICAgcHVibGljIGdldCBpZGVudGlmaWVyKCkge1xuICAgICAgICByZXR1cm4gdGhpcy5zdGF0ZS50b1N0cmluZygpO1xuICAgIH1cblxuICAgIHB1YmxpYyBnZXQgcGF0aCgpOiBub2RlW10ge1xuICAgICAgICBsZXQgcmVzdWx0OiBub2RlW10gPSBbXTtcbiAgICAgICAgbGV0IGN1cnI6IG5vZGV8bnVsbCA9IHRoaXM7XG4gICAgICAgIHdoaWxlIChjdXJyICE9PSBudWxsKSB7XG4gICAgICAgICAgICByZXN1bHQudW5zaGlmdChjdXJyKTtcbiAgICAgICAgICAgIGN1cnIgPSBjdXJyLnBhcmVudDtcbiAgICAgICAgfVxuICAgICAgICByZXR1cm4gcmVzdWx0O1xuICAgIH1cblxuICAgIHB1YmxpYyBnZXRDaGlsZHJlbigpOiBub2RlW10ge1xuICAgICAgICBpZiAodGhpcy5jaGlsZHJlbi5sZW5ndGggIT09IDApIHtcbiAgICAgICAgICAgIHJldHVybiB0aGlzLmNoaWxkcmVuXG4gICAgICAgIH1cbiAgICAgICAgaWYgKHRoaXMuYmxhbmtJbmRleCAlIDMgIT09IDIpIHtcbiAgICAgICAgICAgIC8vQmxhbmsgbW92ZSByaWdodFxuICAgICAgICAgICAgbGV0IG5ld1N0YXRlID0gdGhpcy5zdGF0ZS5zbGljZSgpO1xuICAgICAgICAgICAgQXJyYXlTd2FwSW5kZXgobmV3U3RhdGUsIHRoaXMuYmxhbmtJbmRleCwgdGhpcy5ibGFua0luZGV4KzEpO1xuICAgICAgICAgICAgdGhpcy5jaGlsZHJlbi5wdXNoKG5ldyBub2RlKG5ld1N0YXRlLCB0aGlzLmJsYW5rSW5kZXggKyAxLCB0aGlzKSk7XG4gICAgICAgIH1cbiAgICAgICAgaWYgKHRoaXMuYmxhbmtJbmRleCAlIDMgIT09IDApIHtcbiAgICAgICAgICAgIC8vQmxhbmsgbW92ZSBsZWZ0XG4gICAgICAgICAgICBsZXQgbmV3U3RhdGUgPSB0aGlzLnN0YXRlLnNsaWNlKCk7XG4gICAgICAgICAgICBBcnJheVN3YXBJbmRleChuZXdTdGF0ZSwgdGhpcy5ibGFua0luZGV4LCB0aGlzLmJsYW5rSW5kZXgtMSk7XG4gICAgICAgICAgICB0aGlzLmNoaWxkcmVuLnB1c2gobmV3IG5vZGUobmV3U3RhdGUsIHRoaXMuYmxhbmtJbmRleCAtIDEsIHRoaXMpKTtcbiAgICAgICAgfVxuICAgICAgICBpZiAoTWF0aC5mbG9vcih0aGlzLmJsYW5rSW5kZXggLyAzKSAhPT0gMCkge1xuICAgICAgICAgICAgLy9CbGFuayBtb3ZlIHVwXG4gICAgICAgICAgICBsZXQgbmV3U3RhdGUgPSB0aGlzLnN0YXRlLnNsaWNlKCk7XG4gICAgICAgICAgICBBcnJheVN3YXBJbmRleChuZXdTdGF0ZSwgdGhpcy5ibGFua0luZGV4LCB0aGlzLmJsYW5rSW5kZXgtMyk7XG4gICAgICAgICAgICB0aGlzLmNoaWxkcmVuLnB1c2gobmV3IG5vZGUobmV3U3RhdGUsIHRoaXMuYmxhbmtJbmRleCAtIDMsIHRoaXMpKTtcbiAgICAgICAgfVxuICAgICAgICBpZiAoTWF0aC5mbG9vcih0aGlzLmJsYW5rSW5kZXggLyAzKSAhPT0gMikge1xuICAgICAgICAgICAgLy9CbGFuayBtb3ZlIGRvd25cbiAgICAgICAgICAgIGxldCBuZXdTdGF0ZSA9IHRoaXMuc3RhdGUuc2xpY2UoKTtcbiAgICAgICAgICAgIEFycmF5U3dhcEluZGV4KG5ld1N0YXRlLCB0aGlzLmJsYW5rSW5kZXgsIHRoaXMuYmxhbmtJbmRleCszKTtcbiAgICAgICAgICAgIHRoaXMuY2hpbGRyZW4ucHVzaChuZXcgbm9kZShuZXdTdGF0ZSwgdGhpcy5ibGFua0luZGV4ICsgMywgdGhpcykpO1xuICAgICAgICB9XG4gICAgICAgIHJldHVybiB0aGlzLmNoaWxkcmVuO1xuICAgIH1cbn1cblxuXG5hYnN0cmFjdCBjbGFzcyBzZWFyY2hNZXRob2Qge1xuICAgIHB1YmxpYyBvcGVuVGFibGU6IFByaW9yaXR5UXVldWU8bm9kZT47XG4gICAgcHVibGljIGNsb3NlZFRhYmxlOiB7W2lkOnN0cmluZ106IG5vZGV9O1xuXG4gICAgcHVibGljIGN1cnJlbnROb2RlOiBub2RlO1xuICAgIC8vVGhlIHBhdGggZnJvbSBpbml0aWFsIG5vZGUgdG8gdGhlIGN1cnJlbnQgbm9kZVxuICAgIHByaXZhdGUgdG90YWxTdGVwOiBudW1iZXI7XG5cbiAgICBjb25zdHJ1Y3Rvcihpbml0U3RhdGU6IG51bWJlcltdLCBjdXJyZW50Qmxhbms6IG51bWJlcikge1xuICAgICAgICB0aGlzLm9wZW5UYWJsZSA9IG5ldyBQcmlvcml0eVF1ZXVlPG5vZGU+KHtcbiAgICAgICAgICAgIGNvbXBhcmF0b3I6IGZ1bmN0aW9uIChhOm5vZGUsIGI6bm9kZSkge1xuICAgICAgICAgICAgICAgIHJldHVybiBhLnZhbHVlIC0gYi52YWx1ZTtcbiAgICAgICAgICAgIH0sXG4gICAgICAgIH0pO1xuICAgICAgICB0aGlzLmNsb3NlZFRhYmxlID0ge307XG4gICAgICAgIHRoaXMuY3VycmVudE5vZGUgPSBuZXcgbm9kZShpbml0U3RhdGUsIGN1cnJlbnRCbGFuaywgbnVsbCk7XG4gICAgICAgIHRoaXMub3BlblRhYmxlLnF1ZXVlKHRoaXMuY3VycmVudE5vZGUpO1xuICAgICAgICB0aGlzLm5leHQoKTtcbiAgICAgICAgdGhpcy50b3RhbFN0ZXAgPSAwO1xuICAgIH1cblxuICAgIHB1YmxpYyBuZXh0KCk6IFtudW1iZXJbXSwgbnVtYmVyXSB7XG4gICAgICAgIGlmICh0aGlzLmNoZWNrUmVzdWx0KHRoaXMuY3VycmVudE5vZGUuc3RhdGUpKSB7XG4gICAgICAgICAgICByZXR1cm4gW3RoaXMuY3VycmVudE5vZGUuc3RhdGUsIHRoaXMuY3VycmVudE5vZGUuYmxhbmtJbmRleF07XG4gICAgICAgIH1cbiAgICAgICAgdGhpcy50b3RhbFN0ZXArKztcbiAgICAgICAgaWYgKHRoaXMub3BlblRhYmxlLmxlbmd0aCA9PT0gMCkge1xuICAgICAgICAgICAgYWxlcnQoXCLmkJzntKLlpLHotKVcIik7XG4gICAgICAgICAgICB0aHJvdyBcIkVtcHR5IG9wZW4gdGFibGVcIjtcbiAgICAgICAgfVxuICAgICAgICBsZXQgbmV3Tm9kZSA9IHRoaXMub3BlblRhYmxlLnBlZWsoKTtcbiAgICAgICAgd2hpbGUgKChuZXdOb2RlKS5pZGVudGlmaWVyIGluIHRoaXMuY2xvc2VkVGFibGUpIHtcbiAgICAgICAgICAgIHRoaXMub3BlblRhYmxlLmRlcXVldWUoKTtcbiAgICAgICAgICAgIGlmICh0aGlzLm9wZW5UYWJsZS5sZW5ndGggPT09IDApIHtcbiAgICAgICAgICAgICAgICBhbGVydChcIuaQnOe0ouWksei0pVwiKTtcbiAgICAgICAgICAgICAgICB0aHJvdyBcIkVtcHR5IG9wZW4gdGFibGVcIjtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIG5ld05vZGUgPSB0aGlzLm9wZW5UYWJsZS5wZWVrKCk7XG4gICAgICAgIH1cbiAgICAgICAgdGhpcy5vcGVuVGFibGUuZGVxdWV1ZSgpO1xuICAgICAgICB0aGlzLmNsb3NlZFRhYmxlW25ld05vZGUuaWRlbnRpZmllcl0gPSBuZXdOb2RlO1xuICAgICAgICB0aGlzLmN1cnJlbnROb2RlID0gbmV3Tm9kZTtcbiAgICAgICAgbGV0IGNoaWxkcmVuID0gdGhpcy5jdXJyZW50Tm9kZS5nZXRDaGlsZHJlbigpO1xuICAgICAgICBmb3IgKGxldCBjaGlsZCBvZiBjaGlsZHJlbikge1xuICAgICAgICAgICAgdGhpcy5hZGROZXdPcGVuTm9kZVdpdGhWYWwoY2hpbGQpO1xuICAgICAgICB9XG4gICAgICAgIHJldHVybiBbbmV3Tm9kZS5zdGF0ZSwgbmV3Tm9kZS5ibGFua0luZGV4XTtcbiAgICB9XG5cbiAgICBwdWJsaWMgZ2V0TG93ZXN0Tm9kZSgpIDogbm9kZXx1bmRlZmluZWQge1xuICAgICAgICByZXR1cm4gdGhpcy5vcGVuVGFibGUucGVlaygpO1xuICAgIH1cblxuICAgIHB1YmxpYyBydW5BbGwoKTogYW55IHtcbiAgICAgICAgd2hpbGUgKHRydWUpIHtcbiAgICAgICAgICAgIGxldCBbc3RhdGUsIGJsYW5rXSA9IHRoaXMubmV4dCgpO1xuICAgICAgICAgICAgaWYgKHRoaXMuY2hlY2tSZXN1bHQoc3RhdGUpKSB7XG4gICAgICAgICAgICAgICAgYnJlYWs7XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICB9XG5cbiAgICBwdWJsaWMgY2hlY2tSZXN1bHQoc3RhdGU6IG51bWJlcltdKTogYm9vbGVhbiB7XG4gICAgICAgIGZvciAobGV0IGkgPSAwOyBpIDwgOTsgaSsrKSB7XG4gICAgICAgICAgICBpZiAoc3RhdGVbaV0gIT09IGkpIHtcbiAgICAgICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgfVxuXG4gICAgcHVibGljIGdldCBwYXRoVG9DdXJyZW50KCk6IG5vZGVbXSB7XG4gICAgICAgIHJldHVybiB0aGlzLmN1cnJlbnROb2RlLnBhdGg7XG4gICAgfVxuXG4gICAgcHVibGljIGdldCBzdGVwcygpIHsgcmV0dXJuIHRoaXMudG90YWxTdGVwOyB9XG5cbiAgICBwdWJsaWMgYWJzdHJhY3QgYWRkTmV3T3Blbk5vZGVXaXRoVmFsKG5ld05vZGU6IG5vZGUpOiB2b2lkO1xuXG59XG5cbmNsYXNzIGFTdGFySDEgZXh0ZW5kcyBzZWFyY2hNZXRob2R7XG5cbiAgICBwdWJsaWMgYWRkTmV3T3Blbk5vZGVXaXRoVmFsKG5ld05vZGU6IG5vZGUpOiB2b2lkIHtcbiAgICAgICAgaWYgKCEobmV3Tm9kZS5pZGVudGlmaWVyIGluIHRoaXMuY2xvc2VkVGFibGUpKSB7XG4gICAgICAgICAgICAvL1RoZSBjb3N0IGZyb20gcm9vdCB0byB0aGUgY3VycmVudCBub2RlLCBpLmUgZyoobilcbiAgICAgICAgICAgIGxldCBjdXJyZW50Q29zdCA9IG5ld05vZGUucGF0aC5sZW5ndGg7XG4gICAgICAgICAgICAvL1RoZSBjb3N0IGZyb20gY3VycmVudCBub2RlIHRvIGRlc3RpbmF0aW9uKGgxKihuKSkgaXMgZXN0aW1hdGVkXG4gICAgICAgICAgICAvL2J5IHRoZSBkaXN0YW5jZSBvZiBlYWNoIG1pc3BsYWNlZCBudW1iZXIgdG8gaXRzIGFjdHVhbCBwb3NpdGlvbi5cbiAgICAgICAgICAgIGxldCBlc3RpbWF0ZWRNaW5Db3N0ID0gMDtcbiAgICAgICAgICAgIGZvciAobGV0IGkgPSAwOyBpIDwgbmV3Tm9kZS5zdGF0ZS5sZW5ndGg7IGkrKykge1xuICAgICAgICAgICAgICAgIGlmIChuZXdOb2RlLnN0YXRlW2ldICE9PSBpKSB7XG4gICAgICAgICAgICAgICAgICAgIGVzdGltYXRlZE1pbkNvc3QrKztcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBuZXdOb2RlLnZhbHVlID0gY3VycmVudENvc3QgKyBlc3RpbWF0ZWRNaW5Db3N0IC0gMTtcblxuICAgICAgICAgICAgdGhpcy5vcGVuVGFibGUucXVldWUobmV3Tm9kZSk7XG4gICAgICAgIH1cbiAgICB9XG59XG5cbmNsYXNzIGFTdGFySDIgZXh0ZW5kcyBzZWFyY2hNZXRob2R7XG5cbiAgICBwdWJsaWMgYWRkTmV3T3Blbk5vZGVXaXRoVmFsKG5ld05vZGU6IG5vZGUpOiB2b2lkIHtcbiAgICAgICAgaWYgKCEobmV3Tm9kZS5pZGVudGlmaWVyIGluIHRoaXMuY2xvc2VkVGFibGUpKSB7XG4gICAgICAgICAgICAvL1RoZSBjb3N0IGZyb20gcm9vdCB0byB0aGUgY3VycmVudCBub2RlLCBpLmUgZyoobilcbiAgICAgICAgICAgIGxldCBjdXJyZW50Q29zdCA9IG5ld05vZGUucGF0aC5sZW5ndGg7XG4gICAgICAgICAgICAvL1RoZSBjb3N0IGZyb20gY3VycmVudCBub2RlIHRvIGRlc3RpbmF0aW9uKGgxKihuKSkgaXMgZXN0aW1hdGVkXG4gICAgICAgICAgICAvL2J5IHRoZSBzdW0gb2YgdGhlIGNvbHVtbiBhbmQgcm93IGRpZmZlcmVuY2VzIGluIGVhY2ggbWlzcGxhY2VkIHBvc2l0aW9uLlxuICAgICAgICAgICAgbGV0IGVzdGltYXRlZE1pbkNvc3QgPSAwO1xuICAgICAgICAgICAgZm9yIChsZXQgaSA9IDA7IGkgPCBuZXdOb2RlLnN0YXRlLmxlbmd0aDsgaSsrKSB7XG4gICAgICAgICAgICAgICAgLy9Sb3cgZGlmZmVyZW5jZXNcbiAgICAgICAgICAgICAgICBlc3RpbWF0ZWRNaW5Db3N0ICs9IE1hdGguYWJzKGkvMyAtIG5ld05vZGUuc3RhdGVbaV0vMyk7XG4gICAgICAgICAgICAgICAgLy9Db2x1bW4gZGlmZmVyZW5jZXNcbiAgICAgICAgICAgICAgICBlc3RpbWF0ZWRNaW5Db3N0ICs9IE1hdGguYWJzKGklMyAtIG5ld05vZGUuc3RhdGVbaV0lMyk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBuZXdOb2RlLnZhbHVlID0gY3VycmVudENvc3QgKyBlc3RpbWF0ZWRNaW5Db3N0O1xuXG4gICAgICAgICAgICB0aGlzLm9wZW5UYWJsZS5xdWV1ZShuZXdOb2RlKTtcbiAgICAgICAgfVxuICAgIH1cbn1cblxuY2xhc3MgYmZzIGV4dGVuZHMgc2VhcmNoTWV0aG9kIHtcblxuICAgIHB1YmxpYyBhZGROZXdPcGVuTm9kZVdpdGhWYWwobmV3Tm9kZTogbm9kZSk6IHZvaWQge1xuICAgICAgICBpZiAoIShuZXdOb2RlLmlkZW50aWZpZXIgaW4gdGhpcy5jbG9zZWRUYWJsZSkpIHtcbiAgICAgICAgICAgIG5ld05vZGUudmFsdWUgPSAoPG5vZGU+bmV3Tm9kZS5wYXJlbnQpLnZhbHVlICsgMTtcbiAgICAgICAgICAgIHRoaXMub3BlblRhYmxlLnF1ZXVlKG5ld05vZGUpO1xuICAgICAgICB9XG4gICAgfVxufVxuXG5cblxuIl19