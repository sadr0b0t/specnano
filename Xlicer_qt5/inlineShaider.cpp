#include "inlineShaider.h"

InlineShaider::InlineShaider()
{
}

InlineShaider::~InlineShaider()
{
}

void InlineShaider::setStream(QTextStream *stream)
{
    GCodeOutStream = stream;
}

void InlineShaider::setMaxY(double y)
{
    maxY = y;
}

void InlineShaider::setSlice(QList<Point2D> _slice)
{
    slice.clear();
    slice = _slice;
}

struct poid
{
    Point2D p;
    int id;
};

bool p1leftp2(poid p1, poid p2)
{
    if(p1.p.x < p2.p.x)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QList<poid> search_one_level(Point2D level, QList<Point2D> *set_p, int offset)
{
    QList<Point2D>::iterator it = set_p->begin() + offset + 1;
    QList<poid> result;

    int i = offset + 1;
    poid pd;
    pd.p = level;
    pd.id = offset;
    result.append(pd);

    for(; it < set_p->end(); it++)
    {
        if(it->isOneLevel(level, 0.01))
        {
            pd.p = *it;
            pd.id = i;
            result.append(pd);
        }

        i++;
    }


    if(result.size() > 1)
    {
        qSort(result.begin(), result.end(), p1leftp2);
    }

    return result;
}

void InlineShaider::innerShading(double Z, double F, double scale)
{
    QList<Point2D> set_point(slice);

    if(set_point.size() > 1)
    {
        extend_List(&set_point, scale);
        QList<poid> one_level;

        poid temp1;
        poid temp2;
        Point2D t1_prev, t2_next, t1_next, t2_prev;
        *GCodeOutStream << "\t\tG00 X" << set_point.at(0).x << " Y" << set_point.at(0).y << " Z" << Z << " F" << F << "\r\n";

        int id = -1;
        temp1.p = set_point.at(0);
        temp1.id = 0;
        temp2.p = set_point.at(1);
        temp1.id = 1;

        while(temp1.p.y < maxY && id < set_point.size() - 2)
        {
            qDebug() << "size =" << set_point.size();
            id++;
            qDebug() << "id =" << id;

            if(id == (set_point.size() - 1))
            {
                break;
            }

            temp1.p = set_point.at(id);
            temp1.id = id;
            temp2.p = set_point.at(id + 1);
            temp2.id = id + 1;

            if(temp2.p.y < temp1.p.y || temp1.p.y >= maxY)
            {
                continue;
            }

            one_level = search_one_level(temp1.p, &set_point, id);

            QList<poid>::iterator iter = one_level.begin() + 1;
            temp2 = one_level.at(0);

            for(; iter < one_level.end(); iter++)
            {
                temp1 = temp2;
                temp2 = *iter;
                qDebug() << temp1.id << '\t' << temp2.id;

                if(temp1.id == 0)
                {
                    qDebug() << "!!!1";
                    t1_prev = set_point.at(set_point.size() - 1);
                    qDebug() << "1!!!";
                }
                else
                {
                    t1_prev = set_point.at(temp1.id - 1);
                }

                if(temp1.id == set_point.size() - 1)
                {
                    t1_next = set_point.at(0);
                }
                else
                {
                    t1_next = set_point.at(temp1.id + 1);
                }

                if(temp2.id == 0)
                {
                    t2_prev = set_point.at(set_point.size() - 1);
                }
                else
                {
                    t2_prev = set_point.at(temp2.id - 1);
                }
                if(temp2.id == set_point.size() - 1)
                {
                    t2_next = set_point.at(0);
                }
                else
                {
                    t2_next = set_point.at(temp2.id + 1);
                }

                if((temp1.p.y > t1_prev.y && temp2.p.y > t2_next.y) || (temp1.p.y < t1_next.y && temp2.p.y < t2_prev.y))
                {
                    *GCodeOutStream << "\t\tG00 X" << temp1.p.x << " Y" << temp1.p.y << " Z" << Z << " F" << F << "\r\n";
                    *GCodeOutStream << "\t\tG01 X" << temp2.p.x << " Y" << temp2.p.y << " Z" << Z << " F" << F << "\r\n";
                }
            }
        }
    }
}

void InlineShaider::extend_List(QList<Point2D> *slice, double fragm)
{
    Point2D p0, p1;

    for(int index = 0; index < slice->size(); index++)
    {
        qDebug() << slice->size();

        if(index == slice->size() - 1)
        {
            p1 = slice->at(0);
        }
        else
        {
            p1 = slice->at(index + 1);
        }

        p0 = slice->at(index);
        qDebug() << "p0 (" << p0.x << p0.y << ")";
        qDebug() << "p1 (" << p1.x << p1.y << ")";


        if(p0.x != p1.x && p0.y != p1.y)
        {
            p1.x -= p0.x;
            p1.y -= p0.y;
            double h = p1.x / p1.y;
            qDebug() << "h = " << h;
            int sign = (p1.y > 0) ? 1 : -1;
            int points = p1.y / fragm;
            points *= sign;

            for(int i = 1; i < points; i++)
            {
                double y = p0.y + i * sign * fragm;
                double x = p0.x + y * h - p0.y * h;
                slice->insert(index + 1, Point2D(x, y));
                index++;
/*
                for(int j = 0; j < slice.size(); j++)
                {
                    qDebug() << j << ": " << slice.at(j).x << slice.at(j).y;
                }
*/
            }
        }
        else
        {
            if(p0.x == p1.x && p0.y == p1.y)
            {
                continue;
                /** §©§Х§Ц§г§о §д§С§Ь§а§У §Ю§а§Ю§Ц§Я§д §й§д§а §Ъ§Щ §г§б§Ъ§г§Ь§С §б§а §б§в§Ъ§й§Ъ§Я§Ц §Я§Ц§в§С§Т§а§д§С§р§л§Ц§Ы §ж-§Ъ§Ъ removeAt
                  §µ§Х§С§Э§Ц§Я§Ъ§Ц §Я§Ц §б§в§а§Ъ§г§з§а§Х§Ъ§д, §б§а§п§д§а§Ю§е §с §Х§Ц§Э§С§р §б§в§а§У§Ц§в§Ь§е §е§г§Э§а§У§Ъ§с (!!!) §У §ж-§Ъ§Ъ
                  innerShading §г§Ю. §Я§Ъ§Ш§Ц **/
            }
            else if(p0.x == p1.x)
            {
                int sign = (p1.y > p0.y) ? 1 : -1;
                int points = (p1.y - p0.y) / fragm;
                points *= sign;

                for(int i = 1; i < points; i++)
                {
                    Point2D point(p1.x, p0.y + i * sign * fragm);
                    slice->insert(index + 1, point);
                    index++;
                }
            }
            else if(p0.y == p1.y)
            {
                continue;
            }
        }
    }
}
