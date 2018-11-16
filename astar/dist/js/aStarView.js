"use strict";
/// <reference path="./aStar.ts" />
/// <reference path="./puzzles.d.ts" />
let method;
let runTimeout = -2;
function runBFS() {
    startGame();
    let seq = jqueryElemToNumSeq(pieces);
    method = new bfs(seq, current_blank);
    showInfo();
    addButtons();
}
function showInfo() {
    $("#open-node").text(method.openTable.length.toString());
    $("#total-step").text(method.steps.toString());
    let lowestNode = method.getLowestNode();
    let lowNodeState = lowestNode.state.slice();
    lowNodeState.forEach(function (_, index) {
        lowNodeState[index] += 1;
    });
    $("#open-row1").text(lowNodeState.slice(0, 3).toString());
    $("#open-row2").text(lowNodeState.slice(3, 6).toString());
    $("#open-row3").text(lowNodeState.slice(6, 9).toString());
}
function runAStarH1() {
    startGame();
    let seq = jqueryElemToNumSeq(pieces);
    method = new aStarH1(seq, current_blank);
    showInfo();
    addButtons();
}
function runAStarH2() {
    startGame();
    let seq = jqueryElemToNumSeq(pieces);
    method = new aStarH2(seq, current_blank);
    showInfo();
    runTimeout = setTimeout(goNext, 100);
    addButtons();
}
function jqueryElemToNumSeq(arr) {
    let result = [];
    for (var i = 0; i < 9; i++) {
        var className = arr[i].attr("class");
        result.push(Math.abs(className.slice(className.length - 2)));
    }
    return result;
}
function autoRun() {
    try {
        goNext();
    }
    catch (_a) {
        return;
    }
    if (runTimeout !== -2)
        setTimeout(autoRun, 2);
}
function goNext() {
    if (method.checkResult(method.currentNode.state)) {
        runTimeout = -2;
        $("#button-area").append($("<button>").
            attr("id", "showpath").addClass("click").
            click(function () {
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
        $("#message").text("搜索完成。步数：" + method.steps + ", 路径长度：" + method.pathToCurrent.length);
    }
}
function addButtons() {
    $("#button-area").append($("<button>").
        attr("id", "autorun").addClass("click").
        click(function () {
        if (runTimeout !== -2) {
            clearTimeout(runTimeout);
            runTimeout = -2;
            $("#next").show();
            $("#run-all").show();
            $(this).text("自动运行");
        }
        else {
            runTimeout = setTimeout(autoRun, 1);
            $(this).text("暂停运行");
            $("#next").hide();
            $("#run-all").hide();
        }
    }).text("自动运行"));
    $("#button-area").append($("<button>").
        attr("id", "run-all").addClass("click").
        click(function () {
        method.runAll();
        current_blank = method.currentNode.blankIndex;
        printPicture(method.currentNode.state);
        $("#message").text("搜索完成。步数：" + method.steps + ", 路径长度：" + method.pathToCurrent.length);
        goNext();
        showInfo();
    }).text("直接获取"));
}
//# sourceMappingURL=data:application/json;base64,eyJ2ZXJzaW9uIjozLCJmaWxlIjoiYVN0YXJWaWV3LmpzIiwic291cmNlUm9vdCI6IiIsInNvdXJjZXMiOlsiLi4vLi4vc3JjL2FTdGFyVmlldy50cyJdLCJuYW1lcyI6W10sIm1hcHBpbmdzIjoiO0FBQUEsbUNBQW1DO0FBQ25DLHVDQUF1QztBQUV2QyxJQUFJLE1BQW9CLENBQUM7QUFDekIsSUFBSSxVQUFVLEdBQVcsQ0FBQyxDQUFDLENBQUM7QUFFNUIsU0FBUyxNQUFNO0lBQ1gsU0FBUyxFQUFFLENBQUM7SUFDWixJQUFJLEdBQUcsR0FBRyxrQkFBa0IsQ0FBQyxNQUFNLENBQUMsQ0FBQztJQUNyQyxNQUFNLEdBQUcsSUFBSSxHQUFHLENBQUMsR0FBRyxFQUFFLGFBQWEsQ0FBQyxDQUFDO0lBQ3JDLFFBQVEsRUFBRSxDQUFDO0lBQ1gsVUFBVSxFQUFFLENBQUM7QUFDakIsQ0FBQztBQUVELFNBQVMsUUFBUTtJQUNiLENBQUMsQ0FBQyxZQUFZLENBQUMsQ0FBQyxJQUFJLENBQUMsTUFBTSxDQUFDLFNBQVMsQ0FBQyxNQUFNLENBQUMsUUFBUSxFQUFFLENBQUMsQ0FBQztJQUN6RCxDQUFDLENBQUMsYUFBYSxDQUFDLENBQUMsSUFBSSxDQUFDLE1BQU0sQ0FBQyxLQUFLLENBQUMsUUFBUSxFQUFFLENBQUMsQ0FBQztJQUMvQyxJQUFJLFVBQVUsR0FBRyxNQUFNLENBQUMsYUFBYSxFQUFFLENBQUM7SUFDeEMsSUFBSSxZQUFZLEdBQVUsVUFBVyxDQUFDLEtBQUssQ0FBQyxLQUFLLEVBQUUsQ0FBQztJQUNwRCxZQUFZLENBQUMsT0FBTyxDQUFDLFVBQVUsQ0FBQyxFQUFFLEtBQUs7UUFDbkMsWUFBWSxDQUFDLEtBQUssQ0FBQyxJQUFJLENBQUMsQ0FBQztJQUM3QixDQUFDLENBQUMsQ0FBQztJQUNILENBQUMsQ0FBQyxZQUFZLENBQUMsQ0FBQyxJQUFJLENBQUMsWUFBWSxDQUFDLEtBQUssQ0FBQyxDQUFDLEVBQUUsQ0FBQyxDQUFDLENBQUMsUUFBUSxFQUFFLENBQUMsQ0FBQztJQUMxRCxDQUFDLENB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QUMsTUFBTSxDQUFDLENBQUM7U0FDeEI7YUFBTTtZQUNILFVBQVUsR0FBRyxVQUFVLENBQUMsT0FBTyxFQUFFLENBQUMsQ0FBQyxDQUFDO1lBQ3BDLENBQUMsQ0FBQyxJQUFJLENBQUMsQ0FBQyxJQUFJLENBQUMsTUFBTSxDQUFDLENBQUM7WUFDckIsQ0FBQyxDQUFDLE9BQU8sQ0FBQyxDQUFDLElBQUksRUFBRSxDQUFDO1lBQ2xCLENBQUMsQ0FBQyxVQUFVLENBQUMsQ0FBQyxJQUFJLEVBQUUsQ0FBQztTQUN4QjtJQUNMLENBQUMsQ0FBQyxDQUFDLElBQUksQ0FBQyxNQUFNLENBQUMsQ0FBQyxDQUFDO0lBQ2pCLENBQUMsQ0FBQyxjQUFjLENBQUMsQ0FBQyxNQUFNLENBQUMsQ0FBQyxDQUFDLFVBQVUsQ0FBQztRQUN0QyxJQUFJLENBQUMsSUFBSSxFQUFFLFNBQVMsQ0FBQyxDQUFDLFFBQVEsQ0FBQyxPQUFPLENBQUM7UUFDdkMsS0FBSyxDQUFFO1FBQ0gsTUFBTSxDQUFDLE1BQU0sRUFBRSxDQUFDO1FBQ2hCLGFBQWEsR0FBRyxNQUFNLENBQUMsV0FBVyxDQUFDLFVBQVUsQ0FBQztRQUM5QyxZQUFZLENBQUMsTUFBTSxDQUFDLFdBQVcsQ0FBQyxLQUFLLENBQUMsQ0FBQztRQUN2QyxDQUFDLENBQUMsVUFBVSxDQUFDLENBQUMsSUFBSSxDQUFDLFVBQVUsR0FBQyxNQUFNLENBQUMsS0FBSyxHQUFDLFNBQVMsR0FBQyxNQUFNLENBQUMsYUFBYSxDQUFDLE1BQU0sQ0FBQyxDQUFDO1FBQ2xGLE1BQU0sRUFBRSxDQUFDO1FBQ1QsUUFBUSxFQUFFLENBQUM7SUFDZixDQUFDLENBQUMsQ0FBQyxJQUFJLENBQUMsTUFBTSxDQUFDLENBQUMsQ0FBQztBQUNyQixDQUFDIiwic291cmNlc0NvbnRlbnQiOlsiLy8vIDxyZWZlcmVuY2UgcGF0aD1cIi4vYVN0YXIudHNcIiAvPlxuLy8vIDxyZWZlcmVuY2UgcGF0aD1cIi4vcHV6emxlcy5kLnRzXCIgLz5cblxubGV0IG1ldGhvZDogc2VhcmNoTWV0aG9kO1xubGV0IHJ1blRpbWVvdXQ6IG51bWJlciA9IC0yO1xuXG5mdW5jdGlvbiBydW5CRlMoKTogYW55IHtcbiAgICBzdGFydEdhbWUoKTtcbiAgICBsZXQgc2VxID0ganF1ZXJ5RWxlbVRvTnVtU2VxKHBpZWNlcyk7XG4gICAgbWV0aG9kID0gbmV3IGJmcyhzZXEsIGN1cnJlbnRfYmxhbmspO1xuICAgIHNob3dJbmZvKCk7XG4gICAgYWRkQnV0dG9ucygpO1xufVxuXG5mdW5jdGlvbiBzaG93SW5mbygpOiBhbnkge1xuICAgICQoXCIjb3Blbi1ub2RlXCIpLnRleHQobWV0aG9kLm9wZW5UYWJsZS5sZW5ndGgudG9TdHJpbmcoKSk7XG4gICAgJChcIiN0b3RhbC1zdGVwXCIpLnRleHQobWV0aG9kLnN0ZXBzLnRvU3RyaW5nKCkpO1xuICAgIGxldCBsb3dlc3ROb2RlID0gbWV0aG9kLmdldExvd2VzdE5vZGUoKTtcbiAgICBsZXQgbG93Tm9kZVN0YXRlID0gKDxub2RlPmxvd2VzdE5vZGUpLnN0YXRlLnNsaWNlKCk7XG4gICAgbG93Tm9kZVN0YXRlLmZvckVhY2goZnVuY3Rpb24gKF8sIGluZGV4KSB7XG4gICAgICAgIGxvd05vZGVTdGF0ZVtpbmRleF0gKz0gMTtcbiAgICB9KTtcbiAgICAkKFwiI29wZW4tcm93MVwiKS50ZXh0KGxvd05vZGVTdGF0ZS5zbGljZSgwLCAzKS50b1N0cmluZygpKTtcbiAgICAkKFwiI29wZW4tcm93MlwiKS50ZXh0KGxvd05vZGVTdGF0ZS5zbGljZSgzLCA2KS50b1N0cmluZygpKTtcbiAgICAkKFwiI29wZW4tcm93M1wiKS50ZXh0KGxvd05vZGVTdGF0ZS5zbGljZSg2LCA5KS50b1N0cmluZygpKTtcbn1cblxuZnVuY3Rpb24gcnVuQVN0YXJIMSgpOiBhbnkge1xuICAgIHN0YXJ0R2FtZSgpO1xuICAgIGxldCBzZXEgPSBqcXVlcnlFbGVtVG9OdW1TZXEocGllY2VzKTtcbiAgICBtZXRob2QgPSBuZXcgYVN0YXJIMShzZXEsIGN1cnJlbnRfYmxhbmspO1xuICAgIHNob3dJbmZvKCk7XG4gICAgYWRkQnV0dG9ucygpO1xufVxuXG5mdW5jdGlvbiBydW5BU3RhckgyKCk6IGFueSB7XG4gICAgc3RhcnRHYW1lKCk7XG4gICAgbGV0IHNlcSA9IGpxdWVyeUVsZW1Ub051bVNlcShwaWVjZXMpO1xuICAgIG1ldGhvZCA9IG5ldyBhU3RhckgyKHNlcSwgY3VycmVudF9ibGFuayk7XG4gICAgc2hvd0luZm8oKTtcbiAgICBydW5UaW1lb3V0ID0gc2V0VGltZW91dChnb05leHQsIDEwMCk7XG4gICAgYWRkQnV0dG9ucygpO1xufVxuXG5cbmZ1bmN0aW9uIGpxdWVyeUVsZW1Ub051bVNlcShhcnI6IGFueVtdKTogbnVtYmVyW10ge1xuICAgIGxldCByZXN1bHQ6IG51bWJlcltdID0gW107XG4gICAgZm9yICh2YXIgaSA9IDA7IGkgPCA5OyBpKyspIHtcbiAgICAgICAgdmFyIGNsYXNzTmFtZSA9IGFycltpXS5hdHRyKFwiY2xhc3NcIik7XG4gICAgICAgIHJlc3VsdC5wdXNoKE1hdGguYWJzKGNsYXNzTmFtZS5zbGljZShjbGFzc05hbWUubGVuZ3RoIC0gMikpO1xuICAgIH1cbiAgICByZXR1cm4gcmVzdWx0O1xufVxuXG5mdW5jdGlvbiBhdXRvUnVuKCkge1xuICAgIHRyeSB7XG4gICAgICAgIGdvTmV4dCgpXG4gICAgfSBjYXRjaCB7IHJldHVybjsgfVxuICAgIGlmIChydW5UaW1lb3V0ICE9PSAtMilcbiAgICAgICAgc2V0VGltZW91dChhdXRvUnVuLCAyKTtcbn1cblxuZnVuY3Rpb24gZ29OZXh0KCk6IGFueSB7XG4gICAgaWYgKG1ldGhvZC5jaGVja1Jlc3VsdChtZXRob2QuY3VycmVudE5vZGUuc3RhdGUpKSB7XG4gICAgICAgIHJ1blRpbWVvdXQgPSAtMjtcbiAgICAgICAgJChcIiNidXR0b24tYXJlYVwiKS5hcHBlbmQoJChcIjxidXR0b24+XCIpLlxuICAgICAgICBhdHRyKFwiaWRcIiwgXCJzaG93cGF0aFwiKS5hZGRDbGFzcyhcImNsaWNrXCIpLlxuICAgICAgICBjbGljayggZnVuY3Rpb24gKCkge1xuICAgICAgICAgICAgbGV0IHBhdGggPSBtZXRob2QucGF0aFRvQ3VycmVudDtcbiAgICAgICAgICAgIGN1cnJlbnRfYmxhbmsgPSBwYXRoWzBdLmJsYW5rSW5kZXg7XG4gICAgICAgICAgICBwcmludFBpY3R1cmUocGF0aFswXS5zdGF0ZSk7XG4gICAgICAgICAgICBsZXQgaSA9IDE7XG4gICAgICAgICAgICBzZXRUaW1lb3V0KGZ1bmN0aW9uIGRpc3BsYXlQYXRoKCkge1xuICAgICAgICAgICAgICAgIHBpZWNlc1twYXRoW2krK10uYmxhbmtJbmRleF0ubW92ZUZ1bmMoKTtcbiAgICAgICAgICAgICAgICBpZiAoaSA8IHBhdGgubGVuZ3RoKSB7XG4gICAgICAgICAgICAgICAgICAgIHNldFRpbWVvdXQoZGlzcGxheVBhdGgsIDUwMCk7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfSwgNTAwKTtcbiAgICAgICAgfSkudGV4dChcIuaYvuekuui3r+W+hFwiKSk7XG4gICAgICAgICQoXCIjbmV4dFwiKS5yZW1vdmUoKTtcbiAgICAgICAgJChcIiNhdXRvcnVuXCIpLnJlbW92ZSgpO1xuICAgICAgICAkKFwiI3J1bi1hbGxcIikucmVtb3ZlKCk7XG4gICAgICAgIHJldHVybjtcbiAgICB9XG4gICAgbGV0IFtuZXdTZXEsIG5ld0JsYW5rXSA9IG1ldGhvZC5uZXh0KCk7XG4gICAgc2hvd0luZm8oKTtcbiAgICBjdXJyZW50X2JsYW5rID0gbmV3Qmxhbms7XG4gICAgcHJpbnRQaWN0dXJlKG5ld1NlcSk7XG4gICAgaWYgKG1ldGhvZC5jaGVja1Jlc3VsdChuZXdTZXEpKSB7XG4gICAgICAgICQoXCIjbWVzc2FnZVwiKS50ZXh0KFwi5pCc57Si5a6M5oiQ44CC5q2l5pWw77yaXCIrbWV0aG9kLnN0ZXBzK1wiLCDot6/lvoTplb/luqbvvJpcIittZXRob2QucGF0aFRvQ3VycmVudC5sZW5ndGgpO1xuICAgIH1cbn1cblxuXG5mdW5jdGlvbiBhZGRCdXR0b25zKCkge1xuICAgICQoXCIjYnV0dG9uLWFyZWFcIikuYXBwZW5kKCQoXCI8YnV0dG9uPlwiKS5cbiAgICBhdHRyKFwiaWRcIiwgXCJhdXRvcnVuXCIpLmFkZENsYXNzKFwiY2xpY2tcIikuXG4gICAgY2xpY2soIGZ1bmN0aW9uICgpIHtcbiAgICAgICAgaWYgKHJ1blRpbWVvdXQgIT09IC0yKSB7XG4gICAgICAgICAgICBjbGVhclRpbWVvdXQocnVuVGltZW91dCk7XG4gICAgICAgICAgICBydW5UaW1lb3V0ID0gLTI7XG4gICAgICAgICAgICAkKFwiI25leHRcIikuc2hvdygpO1xuICAgICAgICAgICAgJChcIiNydW4tYWxsXCIpLnNob3coKTtcbiAgICAgICAgICAgICQodGhpcykudGV4dChcIuiHquWKqOi/kOihjFwiKTtcbiAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICAgIHJ1blRpbWVvdXQgPSBzZXRUaW1lb3V0KGF1dG9SdW4sIDEpO1xuICAgICAgICAgICAgJCh0aGlzKS50ZXh0KFwi5pqC5YGc6L+Q6KGMXCIpO1xuICAgICAgICAgICAgJChcIiNuZXh0XCIpLmhpZGUoKTtcbiAgICAgICAgICAgICQoXCIjcnVuLWFsbFwiKS5oaWRlKCk7XG4gICAgICAgIH1cbiAgICB9KS50ZXh0KFwi6Ieq5Yqo6L+Q6KGMXCIpKTtcbiAgICAkKFwiI2J1dHRvbi1hcmVhXCIpLmFwcGVuZCgkKFwiPGJ1dHRvbj5cIikuXG4gICAgYXR0cihcImlkXCIsIFwicnVuLWFsbFwiKS5hZGRDbGFzcyhcImNsaWNrXCIpLlxuICAgIGNsaWNrKCBmdW5jdGlvbiAoKSB7XG4gICAgICAgIG1ldGhvZC5ydW5BbGwoKTtcbiAgICAgICAgY3VycmVudF9ibGFuayA9IG1ldGhvZC5jdXJyZW50Tm9kZS5ibGFua0luZGV4O1xuICAgICAgICBwcmludFBpY3R1cmUobWV0aG9kLmN1cnJlbnROb2RlLnN0YXRlKTtcbiAgICAgICAgJChcIiNtZXNzYWdlXCIpLnRleHQoXCLmkJzntKLlrozmiJDjgILmraXmlbDvvJpcIittZXRob2Quc3RlcHMrXCIsIOi3r+W+hOmVv+W6pu+8mlwiK21ldGhvZC5wYXRoVG9DdXJyZW50Lmxlbmd0aCk7XG4gICAgICAgIGdvTmV4dCgpO1xuICAgICAgICBzaG93SW5mbygpO1xuICAgIH0pLnRleHQoXCLnm7TmjqXojrflj5ZcIikpO1xufVxuXG4iXX0=