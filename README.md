# 📝 Text-Summarizer

This project implements a **Text Summarizer**. It allows users to input text (either from a `.txt` file or entered manually), process it, and return a concise summary by selecting key sentences based on scoring algorithms.

Text summarization is approached in two main ways:
1. **Extractive Summarization** – Selects key sentences directly from the input (*What this project does*)  
2. **Abstractive Summarization** – Generates new phrasing of sentences (*Stuff that GPT does better*)

---

## 🚀 Files Overview

| File        | Description                                             | Scoring Method           |
|-------------|---------------------------------------------------------|--------------------------|
| `ts.cpp`    | Frequency-based text summarizer                         | Word Frequency           |
| `tfIDF.cpp` | TF-IDF enhanced summarizer for better keyword weighting | Term Frequency–Inverse Document Frequency |

---

## 🧠 Implementation Roadmap

1. Input & parse the text  
2. Clean and tokenize the text  
3. Compute sentence scores  
4. Select top-ranked sentences  
5. Display the summary

---

## ⚙️ Core Concepts & Algorithms

1. **Sentence Splitting**: Based on delimiters (e.g. `.`)
2. **Tokenization**: Breaking sentences into words
3. **Cleaning**: Lowercasing and removing punctuation/stopwords
4. **Stopword Filtering**: Ignores common filler words (like "the", "is", etc.)
5. **Scoring Techniques**:
  - `ts.cpp`: Based on **word frequency** per sentence
  - `tfIDF.cpp`: Based on **TF-IDF** score (considers document-wide importance)
6. **Sorting & Selection**: Top sentences chosen based on score percentile
