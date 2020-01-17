/*
 * This file is part of the security-bot project. It has been modified
 * from the original to support more advanced user interaction. However,
 * the original copyright and notices and comments are all preserved.
 * See COPYING file for license
 *
 * Improvements by:
 * Steve Grubb <sgrubb@redhat.com>
 *
 */

#include <QtCore>
#include <unistd.h>
#include <cstddef>
#include "aimlparser.h"

class Task : public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = 0) : QObject(parent) { dump = false; }
    void inline set_dump(void) { dump = true; }

private:
    bool dump;
    void DoEvents();

public slots:
    void run()
    {
	DoEvents();
        emit finished();
    }

signals:
    void finished();
};

void Task::DoEvents()
{
	QString subset("security");
	QString input;

	//Create the parser
	AIMLParser parser(dump ? true : false);
	if (!parser.loadAIMLSet(subset)) {
		if (dump == false)
			printf("Error loading aiml files\n");
		else
			printf("exit - dump true\n");
		return;
	}

	QTextStream qtin(stdin), qtout(stdout);
	QString done("exit"), done2("quit");
	printf("\n");
	printf("The security-bot is ready. Type 'exit' when finished.\n");
	do {
		// get input
		printf("> ");
		QString input = qtin.readLine();

		// Check it
		if (input.trimmed().isEmpty())
			continue;
		if (input == done || input == done2) {
			printf("done\n");
			return;
		}

		// Process it
		QString results = parser.getResponse(input);

		// Output answer
		qtout << results << endl;
	} while (true);
}

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Task parented to the application so that it
    // will be deleted by the application.
    Task *task = new Task(&a);
    if (argc == 2 && strcmp(argv[1], "--dump") == 0)
	task->set_dump();
    else if (getuid()) {
        printf("Come back again some time when you have root.\n");
        return 1;
    }

    // This will cause the application to exit when
    // the task signals finished.    
    QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    QTimer::singleShot(0, task, SLOT(run()));

    return a.exec();
}

