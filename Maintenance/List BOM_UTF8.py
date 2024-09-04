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
	for file_bom_path in Path(location).rglob('*'):
		if file_bom_path.is_file():
			with open(file_bom_path, 'rb') as file_bom:
				data_bom = file_bom.read(len(BOM_UTF8))
				if data_bom == BOM_UTF8:
					print_and_write(file_bom_path, file_log)