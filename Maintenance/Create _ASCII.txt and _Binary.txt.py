from pathlib import Path

excludeds = ('/.git/', '/.idea/')
location = input('Type location: ').replace('"', '')

def get_file_extension(file_name):
	return '*' + file_name[file_name.rfind('.'):]

files_ascii, files_binary = set(["*.txt"]), set()
for file_current_path in Path(location).rglob('*.*'):
	if file_current_path.is_file():
		for excluded in excludeds:
			if excluded in file_current_path.as_posix():
				break
		else:
			file_current_extension = get_file_extension(file_current_path.name)
			try:
				with open(file_current_path, encoding='utf-8') as file_current:
					file_current.read()
				files_ascii.add(file_current_extension)
			except UnicodeDecodeError:
				files_binary.add(file_current_extension)
with open(location + '/_ASCII.txt', 'w', encoding='utf-8', newline='\n') as file_log_ascii:
	file_log_ascii.write('\n'.join(sorted(files_ascii)))
with open(location + '/_Binary.txt', 'w', encoding='utf-8', newline='\n') as file_log_binary:
	file_log_binary.write('\n'.join(sorted(files_binary)))