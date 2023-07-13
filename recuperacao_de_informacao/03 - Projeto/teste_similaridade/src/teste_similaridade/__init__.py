import spacy
nlp = spacy.load('en_core_web_md')

words = "cat dog"

tokens = nlp(words)

token1, token2 = tokens[0], tokens[1]
print("Similarity:", token1.similarity(token2))


