from codecs import BOM_UTF8
from os import fsync
from pathlib import Path

location = input('Type location: ').replace('"', '')

def print_and_write(message, file):
	print(message)
	file.write(str(message) + '\n')
	file.flush()
	fsync(file.fileno())

with open('List BOM_UTF8.txt', 'w', encoding='utf-8', newline='\n') as file_log:
	for file in Path(location).rglob('*.*'):
		if not file.is_dir():
			file_suffix = file.suffix
			if file_suffix == '':
				file_suffix = file.name
			if not file_suffix[1:].islower():
				print_and_write(file, file_log)