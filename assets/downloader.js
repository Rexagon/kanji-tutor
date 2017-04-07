function createDownloadLink(data, id) {
    var blob = new Blob([data], {type: "text/text"});
    var url  = URL.createObjectURL(blob);

    var a = document.createElement('a');
    a.download    = "lesson_" + id + ".json";
    a.href        = url;
    a.textContent = "Download " + a.download;

	document.getElementsByClassName("meaning")[0].appendChild(document.createElement('br'));
	document.getElementsByClassName("meaning")[0].appendChild(a);
}

var lessonList = [];
var kanjiList = [];
var kanjiTable = $(".oneKanji.hideline");

kanjiTable.each(function(key, value) {
	var kanji = {};
    kanji["s"] = $(value).find(".symbol")[0].getAttribute("value");
	kanji["on"] = $($($(value).find(".reading")[0]).find(".readingElem")[0]).text().replace(/\(/g, ', ').replace(/[\)—]/g, '').split(/[\s,、]+/g).filter(function(e) { return e.length > 0 });
	kanji["kun"] = $($($(value).find(".reading")[1]).find(".readingElem")[0]).text().replace(/\(/g, ', ').replace(/[\)—]/g, '').split(/[\s,、]+/g).filter(function(e) { return e.length > 0 });
	kanji["t"] = $($(value).find(".meaning")[0]).text().split(", ");
	kanjiList.push(kanji);	

	if (kanjiList.length == 10) {
		var lesson = {};
		lesson.name = "Урок " + (lessonList.length + 1);
		lesson.kanji = kanjiList;
		lessonList.push(lesson);
		kanjiList = [];

		createDownloadLink(JSON.stringify(lesson, null, '\t'), lessonList.length);
    }
});

if (kanjiList.length > 0) {
	var lesson = {};
	lesson.name = "Урок " + (lessonList.length + 1);
	lesson.kanji = kanjiList;
	lessonList.push(lesson);
	kanjiList = [];

	createDownloadLink(JSON.stringify(lesson, null, '\t'), lessonList.length);
}