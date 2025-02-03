import fs from 'fs';

function tokenize(text) {
  const abbreviations = new Set([
    "Mr.",
    "Dr.",
    "U.S.",
    "Ph.D.",
    "e.g.",
    "i.e.",
  ]);
  let words = text.match(/\b[\w'.-]+\b/g) || [];

  return words.map((word) => {
    if (!abbreviations.has(word) && /[.,!?]$/.test(word)) {
      return word.slice(0, -1);
    }
    return word;
  });
}

function determinePOSTag(word, prevWord) {
  if (/.*ed$/.test(word)) return "VBD"; 
  if (/.*ing$/.test(word)) return "VBG"; 
  if (/.*s$/.test(word)) return "NNS"; 

  if (["a", "an", "the"].includes(prevWord)) return "NN"; 
  if (/^[A-Z]/.test(word) && prevWord) return "NNP"; 
  if (["is", "was", "are"].includes(word)) return "VBZ"; 

  return "NN"; 
}

fs.readFile("D:/WEB DEVLOPMENT/NODE_JS/Tagger/dictionary.txt", "utf8", (err, data) => {
  if (err) {
    console.error("Error opening file!");
    return;
  }

  let words = tokenize(data);
  let taggedWords = [];
  let prevWord = "";

  words.forEach((word) => {
    let posTag = determinePOSTag(word, prevWord);
    taggedWords.push(`${word}/${posTag}`);
    prevWord = word;
  });

  console.log("POS Tagged Text:");
  console.log(taggedWords.join(" "));
});
