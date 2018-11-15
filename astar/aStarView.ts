/// <reference path="./aStar.ts" />
/// <reference path="./aStarView.d.ts" />

let method: searchMethod;
let runTimeout: number = -2;

function runBFS(): any {
    startGame();
    let seq = jqueryElemToNumSeq(pieces);
    method = new bfs(seq, current_blank);
    showInfo();
    addButtons();
}

function showInfo(): any {
    $("#open-node").text(method.openTable.length.toString());
    $("#total-step").text(method.steps.toString());
    let [lowestNode] = method.getLowestNode();
    let lowNodeState = lowestNode.state.slice();
    lowNodeState.forEach(function (_, index) {
        lowNodeState[index] += 1;
    });
    $("#open-row1").text(lowNodeState.slice(0, 3).toString());
    $("#open-row2").text(lowNodeState.slice(3, 6).toString());
    $("#open-row3").text(lowNodeState.slice(6, 9).toString());
}

function runAStarH1(): any {
    startGame();
    let seq = jqueryElemToNumSeq(pieces);
    method = new aStarH1(seq, current_blank);
    showInfo();
    addButtons();
}

function runAStarH2(): any {
    startGame();
    let seq = jqueryElemToNumSeq(pieces);
    method = new aStarH2(seq, current_blank);
    showInfo();
    runTimeout = setTimeout(goNext, 100);
    addButtons();
}


function jqueryElemToNumSeq(arr: any[]): number[] {
    let result: number[] = [];
    for (var i = 0; i < 9; i++) {
        var className = arr[i].attr("class");
        result.push(Math.abs(className.slice(className.length - 2));
    }
    return result;
}

function goNext(): any {
    if (method.checkResult(method.currentNode.state)) {
        clearInterval(runTimeout);
        runTimeout = -2;
        $("#button-area").append($("<button>").
        attr("id", "showpath").addClass("click").
        click( function () {
            let path = method.pathToCurrent;
            current_blank = path[0].blankIndex;
            printPicture(path[0].state);
            let i = 1;
            setTimeout(function displayPath() {
                pieces[path[i++].blankIndex].moveFunc();
                if (i < path.length) {
                    setTimeout(displayPath, 500);
                }
            }, 500);
        }).text("显示路径"));
        $("#next").remove();
        $("#autorun").remove();
        $("#run-all").remove();
        return;
    }
    let [newSeq, newBlank] = method.next();
    showInfo();
    current_blank = newBlank;
    printPicture(newSeq);
    if (method.checkResult(newSeq)) {
        $("#message").text("搜索完成。步数："+method.steps);
    }
}


function addButtons() {
    $("#button-area").append($("<button>").
    attr("id", "autorun").addClass("click").
    click( function () {
        if (runTimeout !== -2) {
            clearTimeout(runTimeout);
            runTimeout = -2;
            $("#next").show();
            $("#run-all").show();
            $(this).text("自动运行");
        } else {
            runTimeout = setInterval(goNext, 1);
            $(this).text("暂停运行");
            $("#next").hide();
            $("#run-all").hide();
        }
    }).text("自动运行"));
    $("#button-area").append($("<button>").
    attr("id", "run-all").addClass("click").
    click( function () {
        method.runAll();
        current_blank = method.currentNode.blankIndex;
        printPicture(method.currentNode.state);
        $("#message").text("搜索完成。步数："+method.steps);
        goNext();
        showInfo();
    }).text("直接获取"));
}


