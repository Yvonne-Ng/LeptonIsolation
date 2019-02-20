From atlasml/ml-base
WORKDIR .
Add . ./
RUN pip install -r requirements.txt --user
CMD ["python3", "isolation.py"]

