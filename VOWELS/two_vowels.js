import fs from 'fs';

function removePunctuation(word) {
    return word.replace(/[^a-zA-Z]/g, '');  
}

function containsConsecutiveVowels(word) {
    const vowelPattern = /[aeiouAEIOU]{2}/;  
    return vowelPattern.test(word);
}

function findWordsWithConsecutiveVowels(filename) {
    fs.readFile(filename, 'utf8', (err, data) => {
        if (err) {
            console.error(`Error opening file ${filename}:`, err);
            return;
        }

        const words = data.split(/\s+/); 
        words.forEach(word => {
            const cleanWord = removePunctuation(word);
            if (containsConsecutiveVowels(cleanWord)) {
                console.log(cleanWord);  
            }
        });
    });
}

findWordsWithConsecutiveVowels('dictionary.txt');
