FROM atlasml/ml-base
WORKDIR .
ADD . ./
RUN pip install -r requirements.txt --user
CMD ["python3", "isolation.py"]

